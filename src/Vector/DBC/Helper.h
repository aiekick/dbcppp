/*
 * Copyright (C) 2019-2019 Julian Hindelang.
 * Contact: tobias.lorenz@gmx.net
 *
 * This file is part of the dbcppp (DBC C++ parser) program.
 *
 * GNU General Public License 3.0 Usage
 * This file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 */

#pragma once

#include <cstdint>

template <class T>
static inline T reverse_bytes_2(T val)
{
	return (((val & 0xFF) << 8ull) |
		((val & 0xFF00) >> 8ull));
}
template <class T>
static inline T reverse_bytes_3(T val)
{
	return (((val & 0xFF) << 16ull) |
		(val & 0xFF00) |
		((val & 0xFF0000) >> 16ull));
}
template <class T>
static inline T reverse_bytes_4(T val)
{
	return (((val & 0xFF) << 24ull) |
		((val & 0xFF00) << 8ull) |
		((val & 0xFF0000) >> 8ull) |
		((val & 0xFF000000) >> 24ul));
}
template <class T>
static inline T reverse_bytes_5(T val)
{
	return (((val & 0xFF) << 32ull) |
		((val & 0xFF00) << 16ull) |
		((val & 0xFF0000)) |
		((val & 0xFF000000) >> 16ull) |
		((val & 0xFF00000000) >> 32ul));
}
template <class T>
static inline T reverse_bytes_6(T val)
{
	return (((val & 0xFF) << 40ull) |
		((val & 0xFF00) << 24ull) |
		((val & 0xFF0000) << 8ull) |
		((val & 0xFF000000) >> 8ull) |
		((val & 0xFF00000000) >> 24ull) |
		((val & 0xFF0000000000) >> 40ul));
}
template <class T>
static inline T reverse_bytes_7(T val)
{
	return (((val & 0xFF) << 48ull) |
		((val & 0xFF00) << 32ull) |
		((val & 0xFF0000) << 16ull) |
		((val & 0xFF000000)) |
		((val & 0xFF00000000) >> 16ull) |
		((val & 0xFF0000000000) >> 32ul) |
		((val & 0xFF000000000000) >> 48ul));
}
template <class T>
static inline T reverse_bytes_8(T val)
{
	return (((val & 0xFF) << 56ull) |
		((val & 0xFF00) << 40ull) |
		((val & 0xFF0000) << 24ull) |
		((val & 0xFF000000) << 8ull) |
		((val & 0xFF00000000) >> 8ull) |
		((val & 0xFF0000000000) >> 24ul) |
		((val & 0xFF000000000000) >> 40ul) |
		((val & 0xFF00000000000000) >> 56ul));
}