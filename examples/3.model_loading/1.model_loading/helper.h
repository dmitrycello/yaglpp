// helper.h
#pragma once
/*LearnOpenGL: utility function for loading a 2D texture from resource id*/
void load_texture(gl::Texture2D& texture, int rcid)
{
    StbImage image(rcid);
    texture.texImage(image, 0);
    texture.generateMipmap();
    texture.textureWrapS = gl::TextureWrapMode::Repeat;
    texture.textureWrapT = gl::TextureWrapMode::Repeat;
    texture.textureMagFilter = gl::TextureMagFilter::Linear;
    texture.textureMinFilter = gl::TextureMinFilter::LinearMipmapLinear;
}
/*LearnOpenGL: utility function for loading a 2D texture from file*/
void load_texture_file(gl::Texture2D& texture, const char* path)
{
    StbImage image(path);
    texture.texImage(image, 0);
    texture.generateMipmap();
    texture.textureWrapS = gl::TextureWrapMode::Repeat;
    texture.textureWrapT = gl::TextureWrapMode::Repeat;
    texture.textureMagFilter = gl::TextureMagFilter::Linear;
    texture.textureMinFilter = gl::TextureMinFilter::LinearMipmapLinear;
}
/*LearnOpenGL: utility function showing a dialog box to retreive a file name and path*/
BOOL open_file(std::string& path, std::string& dir, LPCSTR lpstrTitle, LPCSTR lpstrFilter)
{
    OPENFILENAMEA ofn;
    char buffer[MAX_PATH];
    memset(&ofn, 0, sizeof(OPENFILENAMEA));
    buffer[0] = '\0';
    ofn.lStructSize = sizeof(OPENFILENAMEA);
    ofn.lpstrFilter = lpstrFilter;
    ofn.lpstrFile = buffer;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = lpstrTitle;
    ofn.Flags = OFN_ENABLESIZING | OFN_FILEMUSTEXIST;
    if (GetOpenFileNameA(&ofn))
    {
        path.assign(buffer);
        dir.assign(buffer, ofn.nFileOffset - 1);
        return TRUE;
    }
    else return FALSE;
}
