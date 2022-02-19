#ifndef __MD5_h__
#define __MD5_h__

#include <cstdint>
#include <string>

namespace RFC1321
{
	// MD5 calculation algorithm.
	// RSA Data Security, Inc. MD5 Message-Digest Algorithm (reference implementation of RFC 1321)

	/* MD5
	- converted to C++ class by Frank Thilo (thilo@unix-ag.org) for bzflag (http://www.bzflag.org)
	- minor updates by Tomasz Bielak

	based on:
		md5.h and md5.c
		reference implementation of RFC 1321

	Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
	rights reserved.

	License to copy and use this software is granted provided that it
	is identified as the "RSA Data Security, Inc. MD5 Message-Digest
	Algorithm" in all material mentioning or referencing this software
	or this function.

	License is also granted to make and use derivative works provided
	that such works are identified as "derived from the RSA Data
	Security, Inc. MD5 Message-Digest Algorithm" in all material
	mentioning or referencing the derived work.

	RSA Data Security, Inc. makes no representations concerning either
	the merchantability of this software or the suitability of this
	software for any particular purpose. It is provided "as is"
	without express or implied warranty of any kind.

	These notices must be retained in any copies of any part of this
	documentation and/or software.
	*/

	#define MD5_BLOCKSIZE (64)

	class MD5
	{
	public:
		MD5();
		MD5(const std::string& text);
		MD5(char* input, uint32_t length);

		void update(const uint8_t* buffer, uint32_t size);
		void update(const char* buf, uint32_t length);
		MD5& finalize();

		std::string get() const;

		uint8_t* digestPtr() { return &(_digest[0]); }

	private:
		void init();
		void transform(const uint8_t block[MD5_BLOCKSIZE]);
		static void decode(uint32_t output[], const uint8_t input[], uint32_t len);
		static void encode(uint8_t output[], const uint32_t input[], uint32_t len);

		bool _finalized;
		uint8_t _buffer[64];  // bytes that didn't fit in last 64 byte chunk
		uint32_t _count[2];   // 64bit counter for number of bits (lo, hi)
		uint32_t _state[4];   // digest so far
		uint8_t _digest[16];  // the result

		// low level logic operations
		static inline uint32_t F(uint32_t x, uint32_t y, uint32_t z);
		static inline uint32_t G(uint32_t x, uint32_t y, uint32_t z);
		static inline uint32_t H(uint32_t x, uint32_t y, uint32_t z);
		static inline uint32_t I(uint32_t x, uint32_t y, uint32_t z);
		static inline uint32_t rotate_left(uint32_t x, int n);
		static inline void FF(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
		static inline void GG(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
		static inline void HH(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
		static inline void II(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
	};
}

#endif
