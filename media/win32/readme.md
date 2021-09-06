### Overview
libpng, libjpeg can read decoded RGB(A) image data and image info from file.

Win32 should operate HBITMAP on HDC (which is a kernel object of DeviceContext).

Win32 could not operate RGB(A) image data directly.

RGB(A) image data should be convert to HBITMAP at first, that means a new kernel object should be created.

gdi+ also operate Bitmap on the underlying HDC, and a HBITMAP would be created implicitly.

### WTL
data+info -> HBITMAP
```c++
HBITMAP CreateBitmap(int nWidth, int nHeight, UINT nPlanes, UINT nBitsPerPixel, const void* lpBits)
	{
		ATLASSERT(m_hBitmap == NULL);
		m_hBitmap = ::CreateBitmap(nWidth, nHeight, nPlanes, nBitsPerPixel, lpBits);
		return m_hBitmap;
	}
 ```

### Gdiplus
data+info -> Bitmap
``` c++
inline 
Bitmap::Bitmap(
    IN const BITMAPINFO* gdiBitmapInfo, 
    IN VOID* gdiBitmapData
    )
{
    GpBitmap *bitmap = NULL;

    lastResult = DllExports::GdipCreateBitmapFromGdiDib(gdiBitmapInfo,
                                                        gdiBitmapData,
                                                        &bitmap);

    SetNativeImage(bitmap);
}

HBITMAP -> Bitmap
```c++
inline 
Bitmap::Bitmap(
    IN HBITMAP hbm, 
    IN HPALETTE hpal
    )
{
    GpBitmap *bitmap = NULL;

    lastResult = DllExports::GdipCreateBitmapFromHBITMAP(hbm, hpal, &bitmap);

    SetNativeImage(bitmap);
}
```

Bitmap -> HBITMAP (created)
```c++
inline Status 
Bitmap::GetHBITMAP(
    IN const Color& colorBackground,
    OUT HBITMAP* hbmReturn
    )
{
    return SetStatus(DllExports::GdipCreateHBITMAPFromBitmap(
                                        static_cast<GpBitmap*>(nativeImage),
                                        hbmReturn,
                                        colorBackground.GetValue()));
}
```

File -> Bitmap (use gdi+ decoder)


