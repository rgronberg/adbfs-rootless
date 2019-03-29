/*
 *      Software License Agreement (BSD License)
 *
 *      Copyright (c) 2010-2011, Calvin Tee (collectskin.com)
 *      All rights reserved.
 *
 *      Writen by Rion Gronberg (rion.gronberg@gmail.com)
 *
 *      Redistribution and use in source and binary forms, with or without
 *      modification, are permitted provided that the following conditions are
 *      met:
 *
 *      * Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following disclaimer
 *        in the documentation and/or other materials provided with the
 *        distribution.
 *      * Neither the name of the  nor the names of its
 *        contributors may be used to endorse or promote products derived from
 *        this software without specific prior written permission.
 *
 *      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "cache_manager.h"

#include <iostream>

CacheManager::CacheManager(std::string cache_size_string)
{
    if (!cache_size_string.empty()) {
        uint64_t scale;
        switch (cache_size_string[cache_size_string.length() - 1]) {
            case 'k':
            case 'K':
                scale = 1024;
                break;
            case 'm':
            case 'M':
                scale = 1024 * 1024;
                break;
            case 'g':
            case 'G':
                scale = 1024 * 1024 * 1024;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                scale = 1;
                break;
            default:
                scale = 0;
                std::cerr << "Could not parse suffix: '"
                          << cache_size_string[cache_size_string.length() - 1]
                          << "'" << std::endl;
                break;
        }

        if (scale > 1) {
            cache_size_string = cache_size_string.substr(0, cache_size_string.length() - 1);
        }

        uint64_t raw_cache_size = std::stoi(cache_size_string);

        cache_size = raw_cache_size * scale;
    }
    else {
        cache_size = 0;
    }

    std::cout << "Using cache size of " << cache_size << " bytes" << std::endl;
}
