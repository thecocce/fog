// [Fog/Core Library - Public API]
//
// [Licence]
// MIT, See COPYING file in package

// [Precompiler headers]
#if defined(FOG_PRECOMP)
#include FOG_PRECOMP
#endif // FOG_PRECOMP

// [Dependencies]
#include <Fog/Core/Char.h>

namespace Fog {

// ============================================================================
// [Fog::CharUtil]
// ============================================================================

FOG_CVAR_DECLARE const uint8_t asciiCTypeData[256] =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, // 0
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 16
  0x20, 0x40, 0x40, 0x40, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, // 32
  0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, // 48
  0x40, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, // 64
  0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x40, 0x40, 0x40, 0x40, 0x50, // 80
  0x40, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, // 96
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x40, 0x40, 0x40, 0x40, 0x00, // 112
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 128
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 144
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 160
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 176
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 192
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 208
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 224
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // 240
};

FOG_CVAR_DECLARE const uint8_t asciiCTypeToLowerData[256] =
{
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, // 0
  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, // 16
  0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, // 32
  0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, // 48
  0x40, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, // 64
  0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, // 80
  0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, // 96
  0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, // 112
  0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, // 128
  0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, // 144
  0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, // 160
  0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, // 176
  0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, // 192
  0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, // 208
  0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, // 224
  0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF  // 240
};

FOG_CVAR_DECLARE const uint8_t asciiCTypeToUpperData[256] =
{
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, // 0
  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, // 16
  0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, // 32
  0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, // 48
  0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, // 64
  0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, // 80
  0x60, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, // 96
  0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, // 112
  0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, // 128
  0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, // 144
  0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, // 160
  0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, // 176
  0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, // 192
  0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, // 208
  0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, // 224
  0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF  // 240
};

// This table is from Ultimate++
FOG_CVAR_DECLARE const uint32_t unicodeCTypeData[2048] =
{
  0x00000000,0x00400801,0x00801002,0x00c01803,0x01002004,0x01402805,0x01803006,0x01c03807,
  0x02004008,0x02404809,0x0280500a,0x02c0580b,0x0300600c,0x0340680d,0x0380700e,0x03c0780f,
  0x04008010,0x04408811,0x04809012,0x04c09813,0x0500a014,0x0540a815,0x0580b016,0x05c0b817,
  0x0600c018,0x0640c819,0x0680d01a,0x06c0d81b,0x0700e01c,0x0740e81d,0x0780f01e,0x07c0f81f,
  0x08010020,0x08410821,0x08811022,0x08c11823,0x09012024,0x09412825,0x09813026,0x09c13827,
  0x0a014028,0x0a414829,0x0a81502a,0x0ac1582b,0x0b01602c,0x0b41682d,0x0b81702e,0x0bc1782f,
  0x0c018030,0x0c418831,0x0c819032,0x0cc19833,0x0d01a034,0x0d41a835,0x0d81b036,0x0dc1b837,
  0x0e01c038,0x0e41c839,0x0e81d03a,0x0ec1d83b,0x0f01e03c,0x0f41e83d,0x0f81f03e,0x0fc1f83f,
  0x10020040,0x50420861,0x50821062,0x50c21863,0x51022064,0x51422865,0x51823066,0x51c23867,
  0x52024068,0x52424869,0x5282506a,0x52c2586b,0x5302606c,0x5342686d,0x5382706e,0x53c2786f,
  0x54028070,0x54428871,0x54829072,0x54c29873,0x5502a074,0x5542a875,0x5582b076,0x55c2b877,
  0x5602c078,0x5642c879,0x5682d07a,0x16c2d85b,0x1702e05c,0x1742e85d,0x1782f05e,0x17c2f85f,
  0x18030060,0x98420861,0x98821062,0x98c21863,0x99022064,0x99422865,0x99823066,0x99c23867,
  0x9a024068,0x9a424869,0x9a82506a,0x9ac2586b,0x9b02606c,0x9b42686d,0x9b82706e,0x9bc2786f,
  0x9c028070,0x9c428871,0x9c829072,0x9cc29873,0x9d02a074,0x9d42a875,0x9d82b076,0x9dc2b877,
  0x9e02c078,0x9e42c879,0x9e82d07a,0x1ec3d87b,0x1f03e07c,0x1f43e87d,0x1f83f07e,0x1fc3f87f,
  0x00040080,0x00040881,0x00041082,0x00041883,0x00042084,0x00042885,0x00043086,0x00043887,
  0x00044088,0x00044889,0x0004508a,0x0004588b,0x0004608c,0x0004688d,0x0004708e,0x0004788f,
  0x00048090,0x00048891,0x00049092,0x00049893,0x0004a094,0x0004a895,0x0004b096,0x0004b897,
  0x0004c098,0x0004c899,0x0004d09a,0x0004d89b,0x0004e09c,0x0004e89d,0x0004f09e,0x0004f89f,
  0x000500a0,0x000508a1,0x000510a2,0x000518a3,0x000520a4,0x000528a5,0x000530a6,0x000538a7,
  0x000540a8,0x000548a9,0x800550aa,0x000558ab,0x000560ac,0x000568ad,0x000570ae,0x000578af,
  0x000580b0,0x000588b1,0x000590b2,0x000598b3,0x0005a0b4,0x801ce0b5,0x0005b0b6,0x0005b8b7,
  0x0005c0b8,0x0005c8b9,0x8005d0ba,0x0005d8bb,0x0005e0bc,0x0005e8bd,0x0005f0be,0x0005f8bf,
  0x504600e0,0x504608e1,0x504610e2,0x504618e3,0x504620e4,0x504628e5,0x504630e6,0x50c638e7,
  0x514640e8,0x514648e9,0x514650ea,0x514658eb,0x524660ec,0x524668ed,0x524670ee,0x524678ef,
  0x514680f0,0x538688f1,0x53c690f2,0x53c698f3,0x53c6a0f4,0x53c6a8f5,0x53c6b0f6,0x0006b8d7,
  0x53c6c0f8,0x5546c8f9,0x5546d0fa,0x5546d8fb,0x5546e0fc,0x5646e8fd,0x5506f0fe,0x9cc6f8df,
  0x984600e0,0x984608e1,0x984610e2,0x984618e3,0x984620e4,0x984628e5,0x984630e6,0x98c638e7,
  0x994640e8,0x994648e9,0x994650ea,0x994658eb,0x9a4660ec,0x9a4668ed,0x9a4670ee,0x9a4678ef,
  0x994680f0,0x9b8688f1,0x9bc690f2,0x9bc698f3,0x9bc6a0f4,0x9bc6a8f5,0x9bc6b0f6,0x0007b8f7,
  0x9bc6c0f8,0x9d46c8f9,0x9d46d0fa,0x9d46d8fb,0x9d46e0fc,0x9e46e8fd,0x9d06f0fe,0x9e4bc0ff,
  0x50480101,0x98480101,0x50481103,0x98481103,0x50482105,0x98482105,0x50c83107,0x98c83107,
  0x50c84109,0x98c84109,0x50c8510b,0x98c8510b,0x50c8610d,0x98c8610d,0x5108710f,0x9908710f,
  0x51088111,0x99088111,0x51489113,0x99489113,0x5148a115,0x9948a115,0x5148b117,0x9948b117,
  0x5148c119,0x9948c119,0x5148d11b,0x9948d11b,0x51c8e11d,0x99c8e11d,0x51c8f11f,0x99c8f11f,
  0x51c90121,0x99c90121,0x51c91123,0x99c91123,0x52092125,0x9a092125,0x52093127,0x9a093127,
  0x52494129,0x9a494129,0x5249512b,0x9a49512b,0x5249612d,0x9a49612d,0x5249712f,0x9a49712f,
  0x52498069,0x99024931,0x40099133,0x80099133,0x5289a135,0x9a89a135,0x52c9b137,0x9ac9b137,
  0x9ac9c138,0x5309c93a,0x9b09c93a,0x5309d93c,0x9b09d93c,0x5309e93e,0x9b09e93e,0x5309f940,
  0x9b09f940,0x530a0942,0x9b0a0942,0x538a1944,0x9b8a1944,0x538a2946,0x9b8a2946,0x538a3948,
  0x9b8a3948,0x9b8a4949,0x514a514b,0x994a514b,0x53ca614d,0x9bca614d,0x53ca714f,0x9bca714f,
  0x53ca8151,0x9bca8151,0x400a9153,0x800a9153,0x548aa155,0x9c8aa155,0x548ab157,0x9c8ab157,
  0x548ac159,0x9c8ac159,0x54cad15b,0x9ccad15b,0x54cae15d,0x9ccae15d,0x54caf15f,0x9ccaf15f,
  0x54cb0161,0x9ccb0161,0x550b1163,0x9d0b1163,0x550b2165,0x9d0b2165,0x550b3167,0x9d0b3167,
  0x554b4169,0x9d4b4169,0x554b516b,0x9d4b516b,0x554b616d,0x9d4b616d,0x554b716f,0x9d4b716f,
  0x554b8171,0x9d4b8171,0x554b9173,0x9d4b9173,0x55cba175,0x9dcba175,0x564bb177,0x9e4bb177,
  0x564bc0ff,0x568bc97a,0x9e8bc97a,0x568bd97c,0x9e8bd97c,0x568be97e,0x9e8be97e,0x9b02997f,
  0x988c0180,0x508c0a53,0x508c1183,0x988c1183,0x550c2185,0x9d0c2185,0x53cc3254,0x50cc3988,
  0x98cc3988,0x504c4a56,0x510c5257,0x510c598c,0x990c598c,0x9d0c698d,0x548c71dd,0x54cc7a59,
  0x53cc825b,0x518c8992,0x998c8992,0x51cc9a60,0x51cca263,0x9a0fb195,0x524cb269,0x524cba68,
  0x52ccc199,0x9accc199,0x9b0cd19a,0x9b0cd99b,0x550ce26f,0x538cea72,0x9b91019e,0x53ccfa75,
  0x53cd01a1,0x9bcd01a1,0x53cd11a3,0x9bcd11a3,0x540d21a5,0x9c0d21a5,0x400d3280,0x550d39a8,
  0x9d0d39a8,0x514d4a83,0x800d51aa,0x9d0d59ab,0x550d61ad,0x9d0d61ad,0x550d7288,0x554d79b0,
  0x9d4d79b0,0x554d8a8a,0x558d928b,0x564d99b4,0x9e4d99b4,0x568da9b6,0x9e8da9b6,0x514dba92,
  0x514dc1b9,0x994dc1b9,0x994dd1ba,0x000dd9bb,0x550de1bd,0x9d0de1bd,0x800df1be,0x800fb9bf,
  0x000e01c0,0x000e09c1,0x000e11c2,0x000e19c3,0x510e21c6,0x110e29c5,0x990e21c6,0x530e39c9,
  0x130e41c8,0x9b0e39c9,0x538e51cc,0x138e59cb,0x9b8e51cc,0x504e69ce,0x984e69ce,0x524e79d0,
  0x9a4e79d0,0x53ce89d2,0x9bce89d2,0x554e99d4,0x9d4e99d4,0x554ea9d6,0x9d4ea9d6,0x554eb9d8,
  0x9d4eb9d8,0x554ec9da,0x9d4ec9da,0x554ed9dc,0x9d4ed9dc,0x9d0c71dd,0x504ef1df,0x984ef1df,
  0x504f01e1,0x984f01e1,0x504f11e3,0x984f11e3,0x51cf21e5,0x99cf21e5,0x51cf31e7,0x99cf31e7,
  0x52cf41e9,0x9acf41e9,0x53cf51eb,0x9bcf51eb,0x53cf61ed,0x9bcf61ed,0x514f71ef,0x994f71ef,
  0x9a8f81f0,0x510f89f3,0x110f91f2,0x990f89f3,0x51cfa1f5,0x99cfa1f5,0x520fb195,0x55cfb9bf,
  0x538fc1f9,0x9b8fc1f9,0x504fd1fb,0x984fd1fb,0x504fe1fd,0x984fe1fd,0x53cff1ff,0x9bcff1ff,
  0x50500201,0x98500201,0x50501203,0x98501203,0x51502205,0x99502205,0x51503207,0x99503207,
  0x52504209,0x9a504209,0x5250520b,0x9a50520b,0x53d0620d,0x9bd0620d,0x53d0720f,0x9bd0720f,
  0x54908211,0x9c908211,0x54909213,0x9c909213,0x5550a215,0x9d50a215,0x5550b217,0x9d50b217,
  0x54d0c219,0x9cd0c219,0x5510d21b,0x9d10d21b,0x5650e21d,0x9e50e21d,0x5210f21f,0x9a10f21f,
  0x5391019e,0x00110a21,0x53d11223,0x9bd11223,0x56912225,0x9e912225,0x50513227,0x98513227,
  0x51514229,0x99514229,0x53d1522b,0x9bd1522b,0x53d1622d,0x9bd1622d,0x53d1722f,0x9bd1722f,
  0x53d18231,0x9bd18231,0x56519233,0x9e519233,0x0011a234,0x0011aa35,0x0011b236,0x0011ba37,
  0x0011c238,0x0011ca39,0x0011d23a,0x0011da3b,0x0011e23c,0x0011ea3d,0x0011f23e,0x0011fa3f,
  0x00120240,0x00120a41,0x00121242,0x00121a43,0x00122244,0x00122a45,0x00123246,0x00123a47,
  0x00124248,0x00124a49,0x0012524a,0x00125a4b,0x0012624c,0x00126a4d,0x0012724e,0x00127a4f,
  0x9d128250,0x98528a51,0x9d129252,0x988c0a53,0x9bcc3254,0x98d2aa55,0x990c4a56,0x990c5257,
  0x9c92c258,0x9ccc7a59,0x9cd2d25a,0x9bcc825b,0x9c92e25c,0x9c92ea5d,0x98d2f25e,0x9912fa5f,
  0x99cc9a60,0x9cd30a61,0x80131262,0x99cca263,0x9c932264,0x9d132a65,0x9a133266,0x9a133a67,
  0x9a4cba68,0x9a4cb269,0x8013526a,0x9b135a6b,0x9b13626c,0x9b136a6d,0x9b13726e,0x9d0ce26f,
  0x9d138270,0x9b538a71,0x9b8cea72,0x9b939a73,0x8013a274,0x988cfa75,0x8013b276,0x98d3ba77,
  0x9c13c278,0x9d13ca79,0x9d13d27a,0x9d13da7b,0x9c93e27c,0x9c93ea7d,0x9c93f27e,0x9c93fa7f,
  0x800d3280,0x80140a81,0x9cd41282,0x994d4a83,0x99142284,0x9cd42a85,0x99543286,0x9d143a87,
  0x9d0d7288,0x9d544a89,0x9d4d8a8a,0x9d8d928b,0x9d14628c,0x9d146a8d,0x9d14728e,0x80147a8f,
  0x9e948290,0x9e948a91,0x994dba92,0x99549a93,0x8014a294,0x8014aa95,0x8014b296,0x8014ba97,
  0x8014c298,0x8014ca99,0x98d4d29a,0x8014da9b,0x8014e29c,0x9a94ea9d,0x9d14f29e,0x8014fa9f,
  0x9c5502a0,0x80150aa1,0x801512a2,0x99151aa3,0x991522a4,0x99152aa5,0x9d1532a6,0x9d153aa7,
  0x9d1542a8,0x99954aa9,0x9b1552aa,0x9b155aab,0x801562ac,0x80156aad,0x001572ae,0x00157aaf,
  0x001582b0,0x00158ab1,0x001592b2,0x00159ab3,0x0015a2b4,0x0015aab5,0x0015b2b6,0x0015bab7,
  0x0015c2b8,0x0015cab9,0x0015d2ba,0x0015dabb,0x0015e2bc,0x0015eabd,0x0015f2be,0x0015fabf,
  0x001602c0,0x00160ac1,0x001612c2,0x00161ac3,0x001622c4,0x00162ac5,0x001632c6,0x00163ac7,
  0x001642c8,0x00164ac9,0x001652ca,0x00165acb,0x001662cc,0x00166acd,0x001672ce,0x00167acf,
  0x001682d0,0x00168ad1,0x001692d2,0x00169ad3,0x0016a2d4,0x0016aad5,0x0016b2d6,0x0016bad7,
  0x0016c2d8,0x0016cad9,0x0016d2da,0x0016dadb,0x0016e2dc,0x0016eadd,0x0016f2de,0x0016fadf,
  0x001702e0,0x00170ae1,0x001712e2,0x00171ae3,0x001722e4,0x00172ae5,0x001732e6,0x00173ae7,
  0x001742e8,0x00174ae9,0x001752ea,0x00175aeb,0x001762ec,0x00176aed,0x001772ee,0x00177aef,
  0x001782f0,0x00178af1,0x001792f2,0x00179af3,0x0017a2f4,0x0017aaf5,0x0017b2f6,0x0017baf7,
  0x0017c2f8,0x0017caf9,0x0017d2fa,0x0017dafb,0x0017e2fc,0x0017eafd,0x0017f2fe,0x0017faff,
  0x00180300,0x00180b01,0x00181302,0x00181b03,0x00182304,0x00182b05,0x00183306,0x00183b07,
  0x00184308,0x00184b09,0x0018530a,0x00185b0b,0x0018630c,0x00186b0d,0x0018730e,0x00187b0f,
  0x00188310,0x00188b11,0x00189312,0x00189b13,0x0018a314,0x0018ab15,0x0018b316,0x0018bb17,
  0x0018c318,0x0018cb19,0x0018d31a,0x0018db1b,0x0018e31c,0x0018eb1d,0x0018f31e,0x0018fb1f,
  0x00190320,0x00190b21,0x00191322,0x00191b23,0x00192324,0x00192b25,0x00193326,0x00193b27,
  0x00194328,0x00194b29,0x0019532a,0x00195b2b,0x0019632c,0x00196b2d,0x0019732e,0x00197b2f,
  0x00198330,0x00198b31,0x00199332,0x00199b33,0x0019a334,0x0019ab35,0x0019b336,0x0019bb37,
  0x0019c338,0x0019cb39,0x0019d33a,0x0019db3b,0x0019e33c,0x0019eb3d,0x0019f33e,0x0019fb3f,
  0x001a0340,0x001a0b41,0x001a1342,0x001a1b43,0x001a2344,0x001a2b45,0x001a3346,0x001a3b47,
  0x001a4348,0x001a4b49,0x001a534a,0x001a5b4b,0x001a634c,0x001a6b4d,0x001a734e,0x001a7b4f,
  0x001a8350,0x001a8b51,0x001a9352,0x001a9b53,0x001aa354,0x001aab55,0x001ab356,0x001abb57,
  0x001ac358,0x001acb59,0x001ad35a,0x001adb5b,0x001ae35c,0x001aeb5d,0x001af35e,0x001afb5f,
  0x001b0360,0x001b0b61,0x001b1362,0x001b1b63,0x001b2364,0x001b2b65,0x001b3366,0x001b3b67,
  0x001b4368,0x001b4b69,0x001b536a,0x001b5b6b,0x001b636c,0x001b6b6d,0x001b736e,0x001b7b6f,
  0x001b8370,0x001b8b71,0x001b9372,0x001b9b73,0x001ba374,0x001bab75,0x001bb376,0x001bbb77,
  0x001bc378,0x001bcb79,0x001bd37a,0x001bdb7b,0x001be37c,0x001beb7d,0x001bf37e,0x001bfb7f,
  0x001c0380,0x001c0b81,0x001c1382,0x001c1b83,0x001c2384,0x001c2b85,0x401c33ac,0x001c3b87,
  0x401c43ad,0x401c4bae,0x401c53af,0x001c5b8b,0x401c63cc,0x001c6b8d,0x401c73cd,0x401c7bce,
  0x801c8390,0x401c8bb1,0x401c93b2,0x401c9bb3,0x401ca3b4,0x401cabb5,0x401cb3b6,0x401cbbb7,
  0x401cc3b8,0x401ccbb9,0x401cd3ba,0x401cdbbb,0x401ce3bc,0x401cebbd,0x401cf3be,0x401cfbbf,
  0x401d03c0,0x401d0bc1,0x001d13a2,0x401d1bc3,0x401d23c4,0x401d2bc5,0x401d33c6,0x401d3bc7,
  0x401d43c8,0x401d4bc9,0x401d53ca,0x401d5bcb,0x801c33ac,0x801c43ad,0x801c4bae,0x801c53af,
  0x801d83b0,0x801c8bb1,0x801c93b2,0x801c9bb3,0x801ca3b4,0x801cabb5,0x801cb3b6,0x801cbbb7,
  0x801cc3b8,0x801ccbb9,0x801cd3ba,0x801cdbbb,0x801ce3bc,0x801cebbd,0x801cf3be,0x801cfbbf,
  0x801d03c0,0x801d0bc1,0x801d1bc2,0x801d1bc3,0x801d23c4,0x801d2bc5,0x801d33c6,0x801d3bc7,
  0x801d43c8,0x801d4bc9,0x801d53ca,0x801d5bcb,0x801c63cc,0x801c73cd,0x801c7bce,0x001e7bcf,
  0x801c93d0,0x801cc3d1,0x401e93d2,0x401e9bd3,0x401ea3d4,0x801d33d5,0x801d03d6,0x801ebbd7,
  0x401ec3d9,0x801ec3d9,0x401ed3db,0x801ed3db,0x401ee3dd,0x801ee3dd,0x401ef3df,0x801ef3df,
  0x401f03e1,0x801f03e1,0x401f13e3,0x801f13e3,0x401f23e5,0x801f23e5,0x401f33e7,0x801f33e7,
  0x401f43e9,0x801f43e9,0x401f53eb,0x801f53eb,0x401f63ed,0x801f63ed,0x401f73ef,0x801f73ef,
  0x801cd3f0,0x801d0bf1,0x801d1bf2,0x801f9bf3,0x401fa3b8,0x801cabf5,0x001fb3f6,0x001fbbf7,
  0x001fc3f8,0x001fcbf9,0x001fd3fa,0x001fdbfb,0x001fe3fc,0x001febfd,0x001ff3fe,0x001ffbff,
  0x40200450,0x40200c51,0x40201452,0x40201c53,0x40202454,0x40202c55,0x40203456,0x40203c57,
  0x40204458,0x40204c59,0x4020545a,0x40205c5b,0x4020645c,0x40206c5d,0x4020745e,0x40207c5f,
  0x40208430,0x40208c31,0x40209432,0x40209c33,0x4020a434,0x4020ac35,0x4020b436,0x4020bc37,
  0x4020c438,0x4020cc39,0x4020d43a,0x4020dc3b,0x4020e43c,0x4020ec3d,0x4020f43e,0x4020fc3f,
  0x40210440,0x40210c41,0x40211442,0x40211c43,0x40212444,0x40212c45,0x40213446,0x40213c47,
  0x40214448,0x40214c49,0x4021544a,0x40215c4b,0x4021644c,0x40216c4d,0x4021744e,0x40217c4f,
  0x80208430,0x80208c31,0x80209432,0x80209c33,0x8020a434,0x8020ac35,0x8020b436,0x8020bc37,
  0x8020c438,0x8020cc39,0x8020d43a,0x8020dc3b,0x8020e43c,0x8020ec3d,0x8020f43e,0x8020fc3f,
  0x80210440,0x80210c41,0x80211442,0x80211c43,0x80212444,0x80212c45,0x80213446,0x80213c47,
  0x80214448,0x80214c49,0x8021544a,0x80215c4b,0x8021644c,0x80216c4d,0x8021744e,0x80217c4f,
  0x80200450,0x80200c51,0x80201452,0x80201c53,0x80202454,0x80202c55,0x80203456,0x80203c57,
  0x80204458,0x80204c59,0x8020545a,0x80205c5b,0x8020645c,0x80206c5d,0x8020745e,0x80207c5f,
  0x40230461,0x80230461,0x40231463,0x80231463,0x40232465,0x80232465,0x40233467,0x80233467,
  0x40234469,0x80234469,0x4023546b,0x8023546b,0x4023646d,0x8023646d,0x4023746f,0x8023746f,
  0x40238471,0x80238471,0x40239473,0x80239473,0x4023a475,0x8023a475,0x4023b477,0x8023b477,
  0x4023c479,0x8023c479,0x4023d47b,0x8023d47b,0x4023e47d,0x8023e47d,0x4023f47f,0x8023f47f,
  0x40240481,0x80240481,0x00241482,0x00241c83,0x00242484,0x00242c85,0x00243486,0x00243c87,
  0x00244488,0x00244c89,0x4024548b,0x8024548b,0x4024648d,0x8024648d,0x4024748f,0x8024748f,
  0x40248491,0x80248491,0x40249493,0x80249493,0x4024a495,0x8024a495,0x4024b497,0x8024b497,
  0x4024c499,0x8024c499,0x4024d49b,0x8024d49b,0x4024e49d,0x8024e49d,0x4024f49f,0x8024f49f,
  0x402504a1,0x802504a1,0x402514a3,0x802514a3,0x402524a5,0x802524a5,0x402534a7,0x802534a7,
  0x402544a9,0x802544a9,0x402554ab,0x802554ab,0x402564ad,0x802564ad,0x402574af,0x802574af,
  0x402584b1,0x802584b1,0x402594b3,0x802594b3,0x4025a4b5,0x8025a4b5,0x4025b4b7,0x8025b4b7,
  0x4025c4b9,0x8025c4b9,0x4025d4bb,0x8025d4bb,0x4025e4bd,0x8025e4bd,0x4025f4bf,0x8025f4bf,
  0x402604c0,0x40260cc2,0x80260cc2,0x40261cc4,0x80261cc4,0x40262cc6,0x80262cc6,0x40263cc8,
  0x80263cc8,0x40264cca,0x80264cca,0x40265ccc,0x80265ccc,0x40266cce,0x80266cce,0x00267ccf,
  0x402684d1,0x802684d1,0x402694d3,0x802694d3,0x4026a4d5,0x8026a4d5,0x4026b4d7,0x8026b4d7,
  0x4026c4d9,0x8026c4d9,0x4026d4db,0x8026d4db,0x4026e4dd,0x8026e4dd,0x4026f4df,0x8026f4df,
  0x402704e1,0x802704e1,0x402714e3,0x802714e3,0x402724e5,0x802724e5,0x402734e7,0x802734e7,
  0x402744e9,0x802744e9,0x402754eb,0x802754eb,0x402764ed,0x802764ed,0x402774ef,0x802774ef,
  0x402784f1,0x802784f1,0x402794f3,0x802794f3,0x4027a4f5,0x8027a4f5,0x0027b4f6,0x0027bcf7,
  0x4027c4f9,0x8027c4f9,0x0027d4fa,0x0027dcfb,0x0027e4fc,0x0027ecfd,0x0027f4fe,0x0027fcff,
  0x40280501,0x80280501,0x40281503,0x80281503,0x40282505,0x80282505,0x40283507,0x80283507,
  0x40284509,0x80284509,0x4028550b,0x8028550b,0x4028650d,0x8028650d,0x4028750f,0x8028750f,
  0x00288510,0x00288d11,0x00289512,0x00289d13,0x0028a514,0x0028ad15,0x0028b516,0x0028bd17,
  0x0028c518,0x0028cd19,0x0028d51a,0x0028dd1b,0x0028e51c,0x0028ed1d,0x0028f51e,0x0028fd1f,
  0x00290520,0x00290d21,0x00291522,0x00291d23,0x00292524,0x00292d25,0x00293526,0x00293d27,
  0x00294528,0x00294d29,0x0029552a,0x00295d2b,0x0029652c,0x00296d2d,0x0029752e,0x00297d2f,
  0x00298530,0x40298d61,0x40299562,0x40299d63,0x4029a564,0x4029ad65,0x4029b566,0x4029bd67,
  0x4029c568,0x4029cd69,0x4029d56a,0x4029dd6b,0x4029e56c,0x4029ed6d,0x4029f56e,0x4029fd6f,
  0x402a0570,0x402a0d71,0x402a1572,0x402a1d73,0x402a2574,0x402a2d75,0x402a3576,0x402a3d77,
  0x402a4578,0x402a4d79,0x402a557a,0x402a5d7b,0x402a657c,0x402a6d7d,0x402a757e,0x402a7d7f,
  0x402a8580,0x402a8d81,0x402a9582,0x402a9d83,0x402aa584,0x402aad85,0x402ab586,0x002abd57,
  0x002ac558,0x002acd59,0x002ad55a,0x002add5b,0x002ae55c,0x002aed5d,0x002af55e,0x002afd5f,
  0x002b0560,0x80298d61,0x80299562,0x80299d63,0x8029a564,0x8029ad65,0x8029b566,0x8029bd67,
  0x8029c568,0x8029cd69,0x8029d56a,0x8029dd6b,0x8029e56c,0x8029ed6d,0x8029f56e,0x8029fd6f,
  0x802a0570,0x802a0d71,0x802a1572,0x802a1d73,0x802a2574,0x802a2d75,0x802a3576,0x802a3d77,
  0x802a4578,0x802a4d79,0x802a557a,0x802a5d7b,0x802a657c,0x802a6d7d,0x802a757e,0x802a7d7f,
  0x802a8580,0x802a8d81,0x802a9582,0x802a9d83,0x802aa584,0x802aad85,0x802ab586,0x802c3d87,
  0x002c4588,0x002c4d89,0x002c558a,0x002c5d8b,0x002c658c,0x002c6d8d,0x002c758e,0x002c7d8f,
  0x002c8590,0x002c8d91,0x002c9592,0x002c9d93,0x002ca594,0x002cad95,0x002cb596,0x002cbd97,
  0x002cc598,0x002ccd99,0x002cd59a,0x002cdd9b,0x002ce59c,0x002ced9d,0x002cf59e,0x002cfd9f,
  0x002d05a0,0x002d0da1,0x002d15a2,0x002d1da3,0x002d25a4,0x002d2da5,0x002d35a6,0x002d3da7,
  0x002d45a8,0x002d4da9,0x002d55aa,0x002d5dab,0x002d65ac,0x002d6dad,0x002d75ae,0x002d7daf,
  0x002d85b0,0x002d8db1,0x002d95b2,0x002d9db3,0x002da5b4,0x002dadb5,0x002db5b6,0x002dbdb7,
  0x002dc5b8,0x002dcdb9,0x002dd5ba,0x002dddbb,0x002de5bc,0x002dedbd,0x002df5be,0x002dfdbf,
  0x002e05c0,0x002e0dc1,0x002e15c2,0x002e1dc3,0x002e25c4,0x002e2dc5,0x002e35c6,0x002e3dc7,
  0x002e45c8,0x002e4dc9,0x002e55ca,0x002e5dcb,0x002e65cc,0x002e6dcd,0x002e75ce,0x002e7dcf,
  0x002e85d0,0x002e8dd1,0x002e95d2,0x002e9dd3,0x002ea5d4,0x002eadd5,0x002eb5d6,0x002ebdd7,
  0x002ec5d8,0x002ecdd9,0x002ed5da,0x002edddb,0x002ee5dc,0x002eeddd,0x002ef5de,0x002efddf,
  0x002f05e0,0x002f0de1,0x002f15e2,0x002f1de3,0x002f25e4,0x002f2de5,0x002f35e6,0x002f3de7,
  0x002f45e8,0x002f4de9,0x002f55ea,0x002f5deb,0x002f65ec,0x002f6ded,0x002f75ee,0x002f7def,
  0x002f85f0,0x002f8df1,0x002f95f2,0x002f9df3,0x002fa5f4,0x002fadf5,0x002fb5f6,0x002fbdf7,
  0x002fc5f8,0x002fcdf9,0x002fd5fa,0x002fddfb,0x002fe5fc,0x002fedfd,0x002ff5fe,0x002ffdff,
  0x00300600,0x00300e01,0x00301602,0x00301e03,0x00302604,0x00302e05,0x00303606,0x00303e07,
  0x00304608,0x00304e09,0x0030560a,0x00305e0b,0x0030660c,0x00306e0d,0x0030760e,0x00307e0f,
  0x00308610,0x00308e11,0x00309612,0x00309e13,0x0030a614,0x0030ae15,0x0030b616,0x0030be17,
  0x0030c618,0x0030ce19,0x0030d61a,0x0030de1b,0x0030e61c,0x0030ee1d,0x0030f61e,0x0030fe1f,
  0x00310620,0x00310e21,0x00311622,0x00311e23,0x00312624,0x00312e25,0x00313626,0x00313e27,
  0x00314628,0x00314e29,0x0031562a,0x00315e2b,0x0031662c,0x00316e2d,0x0031762e,0x00317e2f,
  0x00318630,0x00318e31,0x00319632,0x00319e33,0x0031a634,0x0031ae35,0x0031b636,0x0031be37,
  0x0031c638,0x0031ce39,0x0031d63a,0x0031de3b,0x0031e63c,0x0031ee3d,0x0031f63e,0x0031fe3f,
  0x00320640,0x00320e41,0x00321642,0x00321e43,0x00322644,0x00322e45,0x00323646,0x00323e47,
  0x00324648,0x00324e49,0x0032564a,0x00325e4b,0x0032664c,0x00326e4d,0x0032764e,0x00327e4f,
  0x00328650,0x00328e51,0x00329652,0x00329e53,0x0032a654,0x0032ae55,0x0032b656,0x0032be57,
  0x0032c658,0x0032ce59,0x0032d65a,0x0032de5b,0x0032e65c,0x0032ee5d,0x0032f65e,0x0032fe5f,
  0x00330660,0x00330e61,0x00331662,0x00331e63,0x00332664,0x00332e65,0x00333666,0x00333e67,
  0x00334668,0x00334e69,0x0033566a,0x00335e6b,0x0033666c,0x00336e6d,0x0033766e,0x00337e6f,
  0x00338670,0x00338e71,0x00339672,0x00339e73,0x0033a674,0x0033ae75,0x0033b676,0x0033be77,
  0x0033c678,0x0033ce79,0x0033d67a,0x0033de7b,0x0033e67c,0x0033ee7d,0x0033f67e,0x0033fe7f,
  0x00340680,0x00340e81,0x00341682,0x00341e83,0x00342684,0x00342e85,0x00343686,0x00343e87,
  0x00344688,0x00344e89,0x0034568a,0x00345e8b,0x0034668c,0x00346e8d,0x0034768e,0x00347e8f,
  0x00348690,0x00348e91,0x00349692,0x00349e93,0x0034a694,0x0034ae95,0x0034b696,0x0034be97,
  0x0034c698,0x0034ce99,0x0034d69a,0x0034de9b,0x0034e69c,0x0034ee9d,0x0034f69e,0x0034fe9f,
  0x003506a0,0x00350ea1,0x003516a2,0x00351ea3,0x003526a4,0x00352ea5,0x003536a6,0x00353ea7,
  0x003546a8,0x00354ea9,0x003556aa,0x00355eab,0x003566ac,0x00356ead,0x003576ae,0x00357eaf,
  0x003586b0,0x00358eb1,0x003596b2,0x00359eb3,0x0035a6b4,0x0035aeb5,0x0035b6b6,0x0035beb7,
  0x0035c6b8,0x0035ceb9,0x0035d6ba,0x0035debb,0x0035e6bc,0x0035eebd,0x0035f6be,0x0035febf,
  0x003606c0,0x00360ec1,0x003616c2,0x00361ec3,0x003626c4,0x00362ec5,0x003636c6,0x00363ec7,
  0x003646c8,0x00364ec9,0x003656ca,0x00365ecb,0x003666cc,0x00366ecd,0x003676ce,0x00367ecf,
  0x003686d0,0x00368ed1,0x003696d2,0x00369ed3,0x0036a6d4,0x0036aed5,0x0036b6d6,0x0036bed7,
  0x0036c6d8,0x0036ced9,0x0036d6da,0x0036dedb,0x0036e6dc,0x0036eedd,0x0036f6de,0x0036fedf,
  0x003706e0,0x00370ee1,0x003716e2,0x00371ee3,0x003726e4,0x00372ee5,0x003736e6,0x00373ee7,
  0x003746e8,0x00374ee9,0x003756ea,0x00375eeb,0x003766ec,0x00376eed,0x003776ee,0x00377eef,
  0x003786f0,0x00378ef1,0x003796f2,0x00379ef3,0x0037a6f4,0x0037aef5,0x0037b6f6,0x0037bef7,
  0x0037c6f8,0x0037cef9,0x0037d6fa,0x0037defb,0x0037e6fc,0x0037eefd,0x0037f6fe,0x0037feff,
  0x00380700,0x00380f01,0x00381702,0x00381f03,0x00382704,0x00382f05,0x00383706,0x00383f07,
  0x00384708,0x00384f09,0x0038570a,0x00385f0b,0x0038670c,0x00386f0d,0x0038770e,0x00387f0f,
  0x00388710,0x00388f11,0x00389712,0x00389f13,0x0038a714,0x0038af15,0x0038b716,0x0038bf17,
  0x0038c718,0x0038cf19,0x0038d71a,0x0038df1b,0x0038e71c,0x0038ef1d,0x0038f71e,0x0038ff1f,
  0x00390720,0x00390f21,0x00391722,0x00391f23,0x00392724,0x00392f25,0x00393726,0x00393f27,
  0x00394728,0x00394f29,0x0039572a,0x00395f2b,0x0039672c,0x00396f2d,0x0039772e,0x00397f2f,
  0x00398730,0x00398f31,0x00399732,0x00399f33,0x0039a734,0x0039af35,0x0039b736,0x0039bf37,
  0x0039c738,0x0039cf39,0x0039d73a,0x0039df3b,0x0039e73c,0x0039ef3d,0x0039f73e,0x0039ff3f,
  0x003a0740,0x003a0f41,0x003a1742,0x003a1f43,0x003a2744,0x003a2f45,0x003a3746,0x003a3f47,
  0x003a4748,0x003a4f49,0x003a574a,0x003a5f4b,0x003a674c,0x003a6f4d,0x003a774e,0x003a7f4f,
  0x003a8750,0x003a8f51,0x003a9752,0x003a9f53,0x003aa754,0x003aaf55,0x003ab756,0x003abf57,
  0x003ac758,0x003acf59,0x003ad75a,0x003adf5b,0x003ae75c,0x003aef5d,0x003af75e,0x003aff5f,
  0x003b0760,0x003b0f61,0x003b1762,0x003b1f63,0x003b2764,0x003b2f65,0x003b3766,0x003b3f67,
  0x003b4768,0x003b4f69,0x003b576a,0x003b5f6b,0x003b676c,0x003b6f6d,0x003b776e,0x003b7f6f,
  0x003b8770,0x003b8f71,0x003b9772,0x003b9f73,0x003ba774,0x003baf75,0x003bb776,0x003bbf77,
  0x003bc778,0x003bcf79,0x003bd77a,0x003bdf7b,0x003be77c,0x003bef7d,0x003bf77e,0x003bff7f,
  0x003c0780,0x003c0f81,0x003c1782,0x003c1f83,0x003c2784,0x003c2f85,0x003c3786,0x003c3f87,
  0x003c4788,0x003c4f89,0x003c578a,0x003c5f8b,0x003c678c,0x003c6f8d,0x003c778e,0x003c7f8f,
  0x003c8790,0x003c8f91,0x003c9792,0x003c9f93,0x003ca794,0x003caf95,0x003cb796,0x003cbf97,
  0x003cc798,0x003ccf99,0x003cd79a,0x003cdf9b,0x003ce79c,0x003cef9d,0x003cf79e,0x003cff9f,
  0x003d07a0,0x003d0fa1,0x003d17a2,0x003d1fa3,0x003d27a4,0x003d2fa5,0x003d37a6,0x003d3fa7,
  0x003d47a8,0x003d4fa9,0x003d57aa,0x003d5fab,0x003d67ac,0x003d6fad,0x003d77ae,0x003d7faf,
  0x003d87b0,0x003d8fb1,0x003d97b2,0x003d9fb3,0x003da7b4,0x003dafb5,0x003db7b6,0x003dbfb7,
  0x003dc7b8,0x003dcfb9,0x003dd7ba,0x003ddfbb,0x003de7bc,0x003defbd,0x003df7be,0x003dffbf,
  0x003e07c0,0x003e0fc1,0x003e17c2,0x003e1fc3,0x003e27c4,0x003e2fc5,0x003e37c6,0x003e3fc7,
  0x003e47c8,0x003e4fc9,0x003e57ca,0x003e5fcb,0x003e67cc,0x003e6fcd,0x003e77ce,0x003e7fcf,
  0x003e87d0,0x003e8fd1,0x003e97d2,0x003e9fd3,0x003ea7d4,0x003eafd5,0x003eb7d6,0x003ebfd7,
  0x003ec7d8,0x003ecfd9,0x003ed7da,0x003edfdb,0x003ee7dc,0x003eefdd,0x003ef7de,0x003effdf,
  0x003f07e0,0x003f0fe1,0x003f17e2,0x003f1fe3,0x003f27e4,0x003f2fe5,0x003f37e6,0x003f3fe7,
  0x003f47e8,0x003f4fe9,0x003f57ea,0x003f5feb,0x003f67ec,0x003f6fed,0x003f77ee,0x003f7fef,
  0x003f87f0,0x003f8ff1,0x003f97f2,0x003f9ff3,0x003fa7f4,0x003faff5,0x003fb7f6,0x003fbff7,
  0x003fc7f8,0x003fcff9,0x003fd7fa,0x003fdffb,0x003fe7fc,0x003feffd,0x003ff7fe,0x003fffff,
};

static uint32_t doCombine(const uint16_t* s, uint32_t uc)
{
  if (uc <= 0xFFFF)
  {
    uint16_t uc16 = (uint16_t)uc;

    for (; *s; s += 2)
    {
      if (*s == uc16) return s[1];
    }
  }

  return 0;
}

uint32_t unicodeCombine(uint32_t uc, uint32_t comb)
{
  static uint16_t comb300[] =
  {
    0x0041, 0x00C0, 0x0045, 0x00C8, 0x0049, 0x00CC, 0x004F, 0x00D2,
    0x0055, 0x00D9, 0x0061, 0x00E0, 0x0065, 0x00E8, 0x0069, 0x00EC,
    0x006F, 0x00F2, 0x0075, 0x00F9, 0x00DC, 0x01DB, 0x00FC, 0x01DC,
    0x004E, 0x01F8, 0x006E, 0x01F9, 0x0415, 0x0400, 0x0418, 0x040D,
    0x0435, 0x0450, 0x0438, 0x045D, 0
  };
  static uint16_t comb301[] =
  {
    0x0041, 0x00C1, 0x0045, 0x00C9, 0x0049, 0x00CD, 0x004F, 0x00D3,
    0x0055, 0x00DA, 0x0059, 0x00DD, 0x0061, 0x00E1, 0x0065, 0x00E9,
    0x0069, 0x00ED, 0x006F, 0x00F3, 0x0075, 0x00FA, 0x0079, 0x00FD,
    0x0043, 0x0106, 0x0063, 0x0107, 0x004C, 0x0139, 0x006C, 0x013A,
    0x004E, 0x0143, 0x006E, 0x0144, 0x0052, 0x0154, 0x0072, 0x0155,
    0x0053, 0x015A, 0x0073, 0x015B, 0x005A, 0x0179, 0x007A, 0x017A,
    0x00DC, 0x01D7, 0x00FC, 0x01D8, 0x0047, 0x01F4, 0x0067, 0x01F5,
    0x00C5, 0x01FA, 0x00E5, 0x01FB, 0x00C6, 0x01FC, 0x00E6, 0x01FD,
    0x00D8, 0x01FE, 0x00F8, 0x01FF, 0x0308, 0x0344, 0x00A8, 0x0385,
    0x0391, 0x0386, 0x0395, 0x0388, 0x0397, 0x0389, 0x0399, 0x038A,
    0x039F, 0x038C, 0x03A5, 0x038E, 0x03A9, 0x038F, 0x03CA, 0x0390,
    0x03B1, 0x03AC, 0x03B5, 0x03AD, 0x03B7, 0x03AE, 0x03B9, 0x03AF,
    0x03CB, 0x03B0, 0x03BF, 0x03CC, 0x03C5, 0x03CD, 0x03C9, 0x03CE,
    0x03D2, 0x03D3, 0x0413, 0x0403, 0x041A, 0x040C, 0x0433, 0x0453,
    0x043A, 0x045C, 0
  };
  static uint16_t comb302[] =
  {
    0x0041, 0x00C2, 0x0045, 0x00CA, 0x0049, 0x00CE, 0x004F, 0x00D4,
    0x0055, 0x00DB, 0x0061, 0x00E2, 0x0065, 0x00EA, 0x0069, 0x00EE,
    0x006F, 0x00F4, 0x0075, 0x00FB, 0x0043, 0x0108, 0x0063, 0x0109,
    0x0047, 0x011C, 0x0067, 0x011D, 0x0048, 0x0124, 0x0068, 0x0125,
    0x004A, 0x0134, 0x006A, 0x0135, 0x0053, 0x015C, 0x0073, 0x015D,
    0x0057, 0x0174, 0x0077, 0x0175, 0x0059, 0x0176, 0x0079, 0x0177,
    0
  };
  static uint16_t comb303[] =
  {
    0x0041, 0x00C3, 0x004E, 0x00D1, 0x004F, 0x00D5, 0x0061, 0x00E3,
    0x006E, 0x00F1, 0x006F, 0x00F5, 0x0049, 0x0128, 0x0069, 0x0129,
    0x0055, 0x0168, 0x0075, 0x0169, 0 };
  static uint16_t comb304[] =
  {
    0x0041, 0x0100, 0x0061, 0x0101, 0x0045, 0x0112, 0x0065, 0x0113,
    0x0049, 0x012A, 0x0069, 0x012B, 0x004F, 0x014C, 0x006F, 0x014D,
    0x0055, 0x016A, 0x0075, 0x016B, 0x00DC, 0x01D5, 0x00FC, 0x01D6,
    0x00C4, 0x01DE, 0x00E4, 0x01DF, 0x0226, 0x01E0, 0x0227, 0x01E1,
    0x00C6, 0x01E2, 0x00E6, 0x01E3, 0x01EA, 0x01EC, 0x01EB, 0x01ED,
    0x00D6, 0x022A, 0x00F6, 0x022B, 0x00D5, 0x022C, 0x00F5, 0x022D,
    0x022E, 0x0230, 0x022F, 0x0231, 0x0059, 0x0232, 0x0079, 0x0233,
    0x0418, 0x04E2, 0x0438, 0x04E3, 0x0423, 0x04EE, 0x0443, 0x04EF,
    0
  };
  static uint16_t comb305[] =
  {
    0
  };
  static uint16_t comb306[] =
  {
    0x0041, 0x0102, 0x0061, 0x0103, 0x0045, 0x0114, 0x0065, 0x0115,
    0x0047, 0x011E, 0x0067, 0x011F, 0x0049, 0x012C, 0x0069, 0x012D,
    0x004F, 0x014E, 0x006F, 0x014F, 0x0055, 0x016C, 0x0075, 0x016D,
    0x0423, 0x040E, 0x0418, 0x0419, 0x0438, 0x0439, 0x0443, 0x045E,
    0x0416, 0x04C1, 0x0436, 0x04C2, 0x0410, 0x04D0, 0x0430, 0x04D1,
    0x0415, 0x04D6, 0x0435, 0x04D7, 0
  };
  static uint16_t comb307[] =
  {
    0x0043, 0x010A, 0x0063, 0x010B, 0x0045, 0x0116, 0x0065, 0x0117,
    0x0047, 0x0120, 0x0067, 0x0121, 0x0049, 0x0130, 0x005A, 0x017B,
    0x007A, 0x017C, 0x0041, 0x0226, 0x0061, 0x0227, 0x004F, 0x022E,
    0x006F, 0x022F, 0
  };
  static uint16_t comb308[] =
  {
    0x0041, 0x00C4, 0x0045, 0x00CB, 0x0049, 0x00CF, 0x004F, 0x00D6,
    0x0055, 0x00DC, 0x0061, 0x00E4, 0x0065, 0x00EB, 0x0069, 0x00EF,
    0x006F, 0x00F6, 0x0075, 0x00FC, 0x0079, 0x00FF, 0x0059, 0x0178,
    0x0399, 0x03AA, 0x03A5, 0x03AB, 0x03B9, 0x03CA, 0x03C5, 0x03CB,
    0x03D2, 0x03D4, 0x0415, 0x0401, 0x0406, 0x0407, 0x0435, 0x0451,
    0x0456, 0x0457, 0x0410, 0x04D2, 0x0430, 0x04D3, 0x04D8, 0x04DA,
    0x04D9, 0x04DB, 0x0416, 0x04DC, 0x0436, 0x04DD, 0x0417, 0x04DE,
    0x0437, 0x04DF, 0x0418, 0x04E4, 0x0438, 0x04E5, 0x041E, 0x04E6,
    0x043E, 0x04E7, 0x04E8, 0x04EA, 0x04E9, 0x04EB, 0x042D, 0x04EC,
    0x044D, 0x04ED, 0x0423, 0x04F0, 0x0443, 0x04F1, 0x0427, 0x04F4,
    0x0447, 0x04F5, 0x042B, 0x04F8, 0x044B, 0x04F9, 0
  };
  static uint16_t comb309[] =
  {
    0
  };
  static uint16_t comb30A[] =
  {
    0x0041, 0x00C5, 0x0061, 0x00E5, 0x0055, 0x016E, 0x0075, 0x016F,
    0
  };
  static uint16_t comb30B[] =
  {
    0x004F, 0x0150, 0x006F, 0x0151, 0x0055, 0x0170, 0x0075, 0x0171,
    0x0423, 0x04F2, 0x0443, 0x04F3, 0
  };
  static uint16_t comb30C[] =
  {
    0x0043, 0x010C, 0x0063, 0x010D, 0x0044, 0x010E, 0x0064, 0x010F,
    0x0045, 0x011A, 0x0065, 0x011B, 0x004C, 0x013D, 0x006C, 0x013E,
    0x004E, 0x0147, 0x006E, 0x0148, 0x0052, 0x0158, 0x0072, 0x0159,
    0x0053, 0x0160, 0x0073, 0x0161, 0x0054, 0x0164, 0x0074, 0x0165,
    0x005A, 0x017D, 0x007A, 0x017E, 0x0041, 0x01CD, 0x0061, 0x01CE,
    0x0049, 0x01CF, 0x0069, 0x01D0, 0x004F, 0x01D1, 0x006F, 0x01D2,
    0x0055, 0x01D3, 0x0075, 0x01D4, 0x00DC, 0x01D9, 0x00FC, 0x01DA,
    0x0047, 0x01E6, 0x0067, 0x01E7, 0x004B, 0x01E8, 0x006B, 0x01E9,
    0x01B7, 0x01EE, 0x0292, 0x01EF, 0x006A, 0x01F0, 0x0048, 0x021E,
    0x0068, 0x021F, 0
  };
  static uint16_t comb30D[] =
  {
    0
  };
  static uint16_t comb30E[] =
  {
    0
  };
  static uint16_t comb30F[] =
  {
    0x0041, 0x0200, 0x0061, 0x0201, 0x0045, 0x0204, 0x0065, 0x0205,
    0x0049, 0x0208, 0x0069, 0x0209, 0x004F, 0x020C, 0x006F, 0x020D,
    0x0052, 0x0210, 0x0072, 0x0211, 0x0055, 0x0214, 0x0075, 0x0215,
    0x0474, 0x0476, 0x0475, 0x0477, 0
  };
  static uint16_t comb311[] =
  {
    0x0041, 0x0202, 0x0061, 0x0203, 0x0045, 0x0206, 0x0065, 0x0207,
    0x0049, 0x020A, 0x0069, 0x020B, 0x004F, 0x020E, 0x006F, 0x020F,
    0x0052, 0x0212, 0x0072, 0x0213, 0x0055, 0x0216, 0x0075, 0x0217,
    0
  };
  static uint16_t comb31B[] =
  {
    0x004F, 0x01A0, 0x006F, 0x01A1, 0x0055, 0x01AF, 0x0075, 0x01B0,
    0
  };
  static uint16_t comb326[] =
  {
    0x0053, 0x0218, 0x0073, 0x0219, 0x0054, 0x021A, 0x0074, 0x021B,
    0
  };
  static uint16_t comb327[] =
  {
    0x0043, 0x00C7, 0x0063, 0x00E7, 0x0047, 0x0122, 0x0067, 0x0123,
    0x004B, 0x0136, 0x006B, 0x0137, 0x004C, 0x013B, 0x006C, 0x013C,
    0x004E, 0x0145, 0x006E, 0x0146, 0x0052, 0x0156, 0x0072, 0x0157,
    0x0053, 0x015E, 0x0073, 0x015F, 0x0054, 0x0162, 0x0074, 0x0163,
    0x0045, 0x0228, 0x0065, 0x0229, 0
  };
  static uint16_t comb328[] =
  {
    0x0041, 0x0104, 0x0061, 0x0105, 0x0045, 0x0118, 0x0065, 0x0119,
    0x0049, 0x012E, 0x0069, 0x012F, 0x0055, 0x0172, 0x0075, 0x0173,
    0x004F, 0x01EA, 0x006F, 0x01EB, 0
  };
  static uint16_t comb653[] =
  {
    0x0627, 0x0622, 0
  };
  static uint16_t comb654[] =
  {
    0x0627, 0x0623, 0x0648, 0x0624, 0x064A, 0x0626, 0x06D5, 0x06C0,
    0x06C1, 0x06C2, 0x06D2, 0x06D3, 0
  };
  static uint16_t comb655[] =
  {
    0x0627, 0x0625, 0
  };

  static const uint16_t *comb300To30F[] =
  {
    comb300, comb301, comb302, comb303, comb304, comb305, comb306, comb307,
    comb308, comb309, comb30A, comb30B, comb30C, comb30D, comb30E, comb30F,
  };

  if (comb >= 0x0300 && comb <= 0x030F)
  {
    return doCombine(comb300To30F[comb - 0x0300], uc);
  }
  else
  {
    switch (comb)
    {
      case 0x0311: return doCombine(comb311, uc);
      case 0x031B: return doCombine(comb31B, uc);
      case 0x0326: return doCombine(comb326, uc);
      case 0x0327: return doCombine(comb327, uc);
      case 0x0328: return doCombine(comb328, uc);
      case 0x0653: return doCombine(comb653, uc);
      case 0x0654: return doCombine(comb654, uc);
      case 0x0655: return doCombine(comb655, uc);
    }
  }
  return 0;
}

// ============================================================================
// [Fog::utf8LengthTable]
// ============================================================================

// this table is for fast lookup for utf8 character length.
const uint8_t utf8LengthTable[256] =
{
  // Primary 128 chars (Standard ASCII)
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  // Extended 128 chars
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 1 byte, but invalid sequence
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 1 byte, but invalid sequence
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 1 byte, but invalid sequence
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 1 byte, but invalid sequence
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0  // zeros are invalid (too high)
};

} // Fog namespace
