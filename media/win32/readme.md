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


### performance
`Graphics::DrawImage()` calc Matrix, and check out two GpBitmap, one is the source which is the in argurment, the other is the dest which is a GpBitmap of HDC.
```
>	GdiPlus.dll!GpGraphics::DrvDrawImage(class GpRuntime::GpRect const *,class GpBitmap *,int,class PointF const *,class RectF const *,class GpImageAttributes const *,unsigned long)	未知
 	GdiPlus.dll!GpGraphics::DrawImage()	未知
 	GdiPlus.dll!GpGraphics::DrawImage(class GpImage *,class RectF const &,class RectF const &,enum Unit,class GpImageAttributes const *)	未知
 	GdiPlus.dll!GdipDrawImage()	未知
 	GdiPlus.dll!_GdipDrawImageI@16()	未知
```
then

`6A1541E0  call        CopyOnWriteBitmap::PipeLockBits (6A156CC0h) `

then
```
>	GdiPlus.dll!DriverGdi::DrawImage(class DpContext *,class DpBitmap *,class DpBitmap *,class GpRuntime::GpRect const *,struct DpImageAttributes const *,int,class PointF const *,class RectF const *,unsigned long)	未知
 	GdiPlus.dll!GpGraphics::DrvDrawImage(class GpRuntime::GpRect const *,class GpBitmap *,int,class PointF const *,class RectF const *,class GpImageAttributes const *,unsigned long)	未知
 	GdiPlus.dll!GpGraphics::DrawImage()	未知
 	GdiPlus.dll!GpGraphics::DrawImage(class GpImage *,class RectF const &,class RectF const &,enum Unit,class GpImageAttributes const *)	未知
 	GdiPlus.dll!GdipDrawImage()	未知
 	GdiPlus.dll!_GdipDrawImageI@16()	未知
```
then
```
>	GdiPlus.dll!EpScanGdiDci::Start()	未知
 	GdiPlus.dll!DpDriver::DrawImage(class DpContext *,class DpBitmap *,class DpBitmap *,class GpRuntime::GpRect const *,struct DpImageAttributes const *,int,class PointF const *,class RectF const *,unsigned long)	未知
 	GdiPlus.dll!GpGraphics::DrvDrawImage(class GpRuntime::GpRect const *,class GpBitmap *,int,class PointF const *,class RectF const *,class GpImageAttributes const *,unsigned long)	未知
 	GdiPlus.dll!GpGraphics::DrawImage()	未知
 	GdiPlus.dll!GpGraphics::DrawImage(class GpImage *,class RectF const &,class RectF const &,enum Unit,class GpImageAttributes const *)	未知
 	GdiPlus.dll!GdipDrawImage()	未知
 	GdiPlus.dll!_GdipDrawImageI@16()	未知
```
then

`6A160A3B  call        EpScanGdiDci::EmptyBatch (6A15EBD5h)`

`6A160A60  call        EpScanRecord::InternalCalculateNextScanRecord (6A182796h) `

then return from `GdiPlus.dll!EpScanGdiDci::Start()`

`6A15CFDB  call        CreateOutputSpan (6A15D2C0h) `

`6A15D177  call        GpPath::AddRects (6A164500h) `

`6A15D1A9  call        RasterizePath (6A159F40h) `

`EpScanGdiDci::End:`

`6A15484C  call        BitmapPipeInput::~BitmapPipeInput (6A1CE77Fh)  `
