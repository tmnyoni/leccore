//
// zip.cpp - zip implementation
//
// leccore library, part of the liblec library
// Copyright (c) 2019 Alec Musasa (alecmus at live dot com)
//
// Released under the CC-BY-NC 2.0 license. For full details see the file
// LICENSE.txt or go to https://github.com/alecmus/liblec/blob/master/LICENSE.md
//

#include "../zip.h"
#include <thread>
#include <future>
#include <fstream>
#include <iostream>
#include <filesystem>

#define POCO_STATIC

#include <Poco\Zip\Compress.h>
#include <Poco\Delegate.h>
#include <Poco\File.h>

// cater for GetAdaptersInfo in PocoFoundationmdd.lib
#pragma comment(lib, "iphlpapi.lib")

using namespace liblec::leccore;

class zip::impl {
public:
	std::string filename_;
	std::vector<std::string> entries_;
	bool add_root_;

	struct zip_result {
		bool success = false;
		std::string error;
	};

	std::future<zip_result> fut_;

	impl() :
		add_root_(true) {}
	~impl() {}

	static zip_result zip_func(impl* p_impl) {
		impl& d_ = *p_impl;

		zip_result result = {};

		if (d_.filename_.empty()) {
			result.error = "Destination file not specified";
			result.success = false;
			return result;
		}

		if (d_.entries_.empty()) {
			result.error = "Zip archive entries not specified";
			result.success = false;
			return result;
		}

		try {
			Poco::File file(d_.filename_);

			if (file.exists() && !file.canWrite()) {
				result.error = "File cannot be written to";
				result.success = false;
				return result;
			}

			std::ofstream out(d_.filename_, std::ios::binary | std::ios::trunc);
			Poco::Zip::Compress compress(out, true);

			for (const auto& it : d_.entries_) {
				Poco::File file(it);

				if (file.exists()) {
					Poco::Path entry(it);

					if (entry.isDirectory()) {
						entry.makeDirectory();
						const bool add_root = d_.add_root_ ? true : d_.entries_.size() > 1;
						compress.addRecursive(entry, Poco::Zip::ZipCommon::CompressionLevel::CL_NORMAL, !add_root);
					}
					else {
						entry.makeFile();
						compress.addFile(entry, entry, Poco::Zip::ZipCommon::CompressionMethod::CM_DEFLATE,
							Poco::Zip::ZipCommon::CompressionLevel::CL_NORMAL);
					}
				}
			}

			compress.close();
			result.success = true;
			return result;
		}
		catch (Poco::Exception& e) {
			result.error = e.displayText();
			result.success = false;
			return result;
		}
	}
};

zip::zip() : d_(*new impl()) {}
zip::~zip() {
	if (d_.fut_.valid())
		d_.fut_.get();

	delete& d_;
}

void zip::start(const std::string& filename,
	const std::vector<std::string>& entries) {
	if (zipping()) {
		// allow only one instance
		return;
	}

	d_.filename_ = filename;
	d_.entries_ = entries;

	// run task asynchronously
	d_.fut_ = std::async(std::launch::async, d_.zip_func, &d_);
	return;
}

bool zip::zipping() {
	if (d_.fut_.valid())
		return d_.fut_.wait_for(std::chrono::seconds{ 0 }) != std::future_status::ready;
	else
		return false;
}

bool zip::result(std::string& error) {
	error.clear();

	if (zipping()) {
		error = "Task not yet complete";
		return false;
	}

	if (d_.fut_.valid()) {
		auto result = d_.fut_.get();
		error = result.error;
		return result.success;
	}

	error = "unexpected error";
	return false;
}
