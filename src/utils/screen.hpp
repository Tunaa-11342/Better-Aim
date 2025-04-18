#pragma once

#define GetBlue(rgb)     (LOBYTE(rgb))
#define GetGreen(rgb)    (LOBYTE(((WORD)(rgb)) >> 8))
#define GetRed(rgb)      (LOBYTE((rgb)>>16))

inline bool findOurTarget(unsigned int* pixels, int width, int height, int tolerance) {
    Color targetColor = Color(config.targetColor.c_str());

    int lowerR = targetColor.r - tolerance, upperR = targetColor.r + tolerance;
    int lowerG = targetColor.g - tolerance, upperG = targetColor.g + tolerance;
    int lowerB = targetColor.b - tolerance, upperB = targetColor.b + tolerance;

    for (int i = 0; i < width * height; ++i) {
        unsigned int pixelColor = pixels[i];
        int r = GetRed(pixelColor), g = GetGreen(pixelColor), b = GetBlue(pixelColor);

        if ((r >= lowerR && r <= upperR) && (g >= lowerG && g <= upperG) && (b >= lowerB && b <= upperB)) {
            return true;
        }
    }

    return false;
}

unsigned int* get_screenshot(int crop_width, int crop_height) {
    int screen_width = GetSystemMetrics(SM_CXSCREEN);
    int screen_height = GetSystemMetrics(SM_CYSCREEN);

    int crop_x = (screen_width - crop_width) / 2;
    int crop_y = (screen_height - crop_height) / 2;

    HDC screen_dc = GetDC(nullptr);
    if (!screen_dc) {
        std::cerr << "Failed to get device context" << std::endl;
        return nullptr;
    }

    HDC mem_dc = CreateCompatibleDC(screen_dc);
    if (!mem_dc) {
        std::cerr << "Failed to create a compatible device context" << std::endl;
        ReleaseDC(nullptr, screen_dc);
        return nullptr;
    }

    HBITMAP bitmap = CreateCompatibleBitmap(screen_dc, crop_width, crop_height);
    if (!bitmap) {
        std::cerr << "Failed to create a compatible bitmap" << std::endl;
        DeleteDC(mem_dc);
        ReleaseDC(nullptr, screen_dc);
        return nullptr;
    }

    SelectObject(mem_dc, bitmap);

    if (!BitBlt(mem_dc, 0, 0, crop_width, crop_height, screen_dc, crop_x, crop_y, SRCCOPY)) {
        std::cerr << "Unable to crop crop your screen :(" << std::endl;
        DeleteObject(bitmap);
        DeleteDC(mem_dc);
        ReleaseDC(nullptr, screen_dc);
        return nullptr;
    }

    BITMAPINFOHEADER bmp_info_header = {};
    bmp_info_header.biSize = sizeof(BITMAPINFOHEADER);
    bmp_info_header.biWidth = crop_width;
    bmp_info_header.biHeight = -crop_height; // Negative for top-down DIB
    bmp_info_header.biPlanes = 1;
    bmp_info_header.biBitCount = 32;
    bmp_info_header.biCompression = BI_RGB;

    std::unique_ptr<unsigned int[]> pixels = std::make_unique<unsigned int[]>(config.scanAreaX * config.scanAreaY);

    if (!pixels) {
        std::cerr << "Failed to allocate space in memory for our pixels :p" << std::endl;
        DeleteObject(bitmap);
        DeleteDC(mem_dc);
        ReleaseDC(nullptr, screen_dc);
        return nullptr;
    }

    if (!GetDIBits(mem_dc, bitmap, 0, crop_height, pixels.get(), reinterpret_cast<BITMAPINFO*>(&bmp_info_header), DIB_RGB_COLORS)) {
        std::cerr << "Failed to retreive bits of the compatible bitmap" << std::endl;
        DeleteObject(bitmap);
        DeleteDC(mem_dc);
        ReleaseDC(nullptr, screen_dc);
        return nullptr;
    }

    DeleteObject(bitmap);
    DeleteDC(mem_dc);
    ReleaseDC(nullptr, screen_dc);

    return pixels.release();
}

// Optional function to save the captured area into a file
bool pixelsToBMP(const char* fileName, unsigned int* pixels, int w, int h) {
    FILE* file = fopen(fileName, "wb");
    if (file) {
        BITMAPFILEHEADER bmp_file_header = {};
        bmp_file_header.bfType = 0x4D42; // "BM"
        bmp_file_header.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (w * h * 4);
        bmp_file_header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

        BITMAPINFOHEADER bmp_info_header = {};
        bmp_info_header.biSize = sizeof(BITMAPINFOHEADER);
        bmp_info_header.biWidth = w;
        bmp_info_header.biHeight = -h; // Negative for top-down DIB
        bmp_info_header.biPlanes = 1;
        bmp_info_header.biBitCount = 32;
        bmp_info_header.biCompression = BI_RGB;

        fwrite(&bmp_file_header, sizeof(BITMAPFILEHEADER), 1, file);
        fwrite(&bmp_info_header, sizeof(BITMAPINFOHEADER), 1, file);
        fwrite(pixels, w * h * 4, 1, file);

        fclose(file);
        return true;
    }
    else {
        std::cerr << "ERROR: fopen() failed!" << std::endl;
        return false;
    }
}