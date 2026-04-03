#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_FRAMEBUFFERS_H
#define YAGLPP_FRAMEBUFFERS_H

#ifdef YAGLPP_VERSION_3_0
namespace gl {
/*(3.0) OpenGL untyped framebuffer object class derived from <Objects>. Can be used as a temporary asset before its reference is casted to any valid framebuffer type*/
class Framebuffers : public Objects
{
public:
	using Objects::Objects;
	enum class Attachment : GLenum;
	enum class AttachmentType : GLenum;
	enum class CompletenessStatus : GLenum;
	/*(3.0) Allocates an array of framebuffer objects of a given size, and generates their object names. Must be deallocated with <Framebuffers::Dealloc> after use
	@param The number of the array elements
	@return The pointer to allocated array*/
	static Framebuffers* Alloc(GLsizei n)
	{
		return (Framebuffers*)object_alloc(glGenFramebuffers, n);
	}

	/*(3.0) Deletes previously allocated array of framebuffer object names, and deallocates its memory block
	@param The pointer to allocated array*/
	static void Dealloc(Framebuffers* framebuffers)
	{
		object_dealloc(glDeleteFramebuffers, (GLuint*)framebuffers);
	}

	/*(3.0) Deletes valid OpenGL framebuffer object name and sets the framebuffer class object in empty state*/
	void Delete()
	{
		object_delete(glDeleteFramebuffers);
	}

	/*(3.0) Deletes previously generated OpenGL framebuffer object names in a static array or a user-defined structure of framebuffers, namely framebuffer map, and sets its class objects in empty state. Allows to unset multiple framebuffers of various types in one function call. The class objects previously set in empty state are silently ignored
	@param The size in bytes of framebuffer map returned by sizeof operator
	@param [in-out] Pointer to framebuffer map*/
	static void DeleteMap(GLsizei n, _Inout_updates_(n) void* framebufferMap)
	{
		object_delete_map(glDeleteFramebuffers, n, framebufferMap);
	}

	/*(3.0) Generates OpenGL framebuffer object name in an empty framebuffer class object*/
	void Gen()
	{
		object_gen(glGenFramebuffers);
	}

	/*(3.0) Generates OpenGL framebuffer object names in a static array or a user-defined structure of framebuffers, namely framebuffer map. Allows to set multiple framebuffers of various types in one function call. All class objects are silently overwritten
	@param The size in bytes of framebuffer map returned by sizeof operator
	@param [out] Pointer to framebuffer map*/
	static void GenMap(GLsizei n, _Out_writes_(n) void* framebufferMap)
	{
		object_gen_map(glGenFramebuffers, n, framebufferMap);
	}

	/*(3.0) Determines if a valid OpenGL framebuffer object name corresponds to a framebuffer object. MSVC getter for <framebuffer> property
	@return True if active framebuffer object, false otherwise*/
	GLboolean IsFramebuffer() const
	{
		return object_is(glIsFramebuffer);
	}

	/*(3.0) Converts index value to color attachment unit within framebuffer attachment enumerator
	@param The index of color attachment unit, must be between 0 and value returned by <GetMaxColorAttachments> minus 1
	@return Color attachment unit value within framebuffer attachment enumerator*/
	constexpr Attachment UnitToAttachment(ColorAttachment index)
	{
		return (Attachment)(GL_COLOR_ATTACHMENT0 + (GLenum)index);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if active framebuffer object*/
	__declspec(property(get = IsFramebuffer)) GLboolean framebuffer;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

protected:
	void auto_delete() { if (IsFramebuffer()) Delete(); }
	static void blit_framebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLuint read, GLuint draw, GLenum mask, GLenum filter);
	GLenum check_framebuffer_status(GLenum target, GLenum binding);
	void framebuffer_renderbuffer(GLenum target, GLenum binding, GLenum attachment, GLuint renderbuffer);
	void framebuffer_texture_1d(GLenum target, GLenum binding, GLenum attachment, GLuint texture, GLint level);
	void framebuffer_texture_2d(GLenum target, GLenum binding, GLenum attachment, GLuint texture, GLenum textarget, GLenum texbinding, GLint level);
	void framebuffer_texture_3d(GLenum target, GLenum binding, GLenum attachment, GLuint texture, GLint level, GLint layer);
	void framebuffer_texture_layer(GLenum target, GLenum binding, GLenum attachment, GLuint texture, GLenum texbinding, GLint level, GLint layer);
	GLint get_framebuffer_attachment_parameter(GLenum target, GLenum binding, GLenum attachment, GLenum pname);

#ifdef YAGLPP_VERSION_3_2
	void framebuffer_texture(GLenum target, GLenum binding, GLenum attachment, GLuint texture, GLenum textarget, GLenum texbinding, GLint level);
#endif // #ifdef YAGLPP_VERSION_3_2
}; // class Framebuffers : public Objects

/*(3.0) GLAD type and color framebuffer attachment point enumerator*/
enum class Framebuffers::Attachment : GLenum
{
	/*(3.0) Framebuffer depth and stencil attachment type*/
	DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT,

	/*(3.0) Framebuffer color attachment unit 0*/
	Color0 = GL_COLOR_ATTACHMENT0,

	/*(3.0) Framebuffer color attachment unit 1*/
	Color1 = GL_COLOR_ATTACHMENT1,

	/*(3.0) Framebuffer color attachment unit 2*/
	Color2 = GL_COLOR_ATTACHMENT2,

	/*(3.0) Framebuffer color attachment unit 3*/
	Color3 = GL_COLOR_ATTACHMENT3,

	/*(3.0) Framebuffer color attachment unit 4*/
	Color4 = GL_COLOR_ATTACHMENT4,

	/*(3.0) Framebuffer color attachment unit 5*/
	Color5 = GL_COLOR_ATTACHMENT5,

	/*(3.0) Framebuffer color attachment unit 6*/
	Color6 = GL_COLOR_ATTACHMENT6,

	/*(3.0) Framebuffer color attachment unit 7*/
	Color7 = GL_COLOR_ATTACHMENT7,

	/*(3.0) Framebuffer color attachment unit 8*/
	Color8 = GL_COLOR_ATTACHMENT8,

	/*(3.0) Framebuffer color attachment unit 9*/
	Color9 = GL_COLOR_ATTACHMENT9,

	/*(3.0) Framebuffer color attachment unit 10*/
	Color10 = GL_COLOR_ATTACHMENT10,

	/*(3.0) Framebuffer color attachment unit 11*/
	Color11 = GL_COLOR_ATTACHMENT11,

	/*(3.0) Framebuffer color attachment unit 12*/
	Color12 = GL_COLOR_ATTACHMENT12,

	/*(3.0) Framebuffer color attachment unit 13*/
	Color13 = GL_COLOR_ATTACHMENT13,

	/*(3.0) Framebuffer color attachment unit 14*/
	Color14 = GL_COLOR_ATTACHMENT14,

	/*(3.0) Framebuffer color attachment unit 15*/
	Color15 = GL_COLOR_ATTACHMENT15,

	/*(3.0) Framebuffer color attachment unit 16*/
	Color16 = GL_COLOR_ATTACHMENT16,

	/*(3.0) Framebuffer color attachment unit 17*/
	Color17 = GL_COLOR_ATTACHMENT17,

	/*(3.0) Framebuffer color attachment unit 18*/
	Color18 = GL_COLOR_ATTACHMENT18,

	/*(3.0) Framebuffer color attachment unit 19*/
	Color19 = GL_COLOR_ATTACHMENT19,

	/*(3.0) Framebuffer color attachment unit 20*/
	Color20 = GL_COLOR_ATTACHMENT20,

	/*(3.0) Framebuffer color attachment unit 21*/
	Color21 = GL_COLOR_ATTACHMENT21,

	/*(3.0) Framebuffer color attachment unit 22*/
	Color22 = GL_COLOR_ATTACHMENT22,

	/*(3.0) Framebuffer color attachment unit 23*/
	Color23 = GL_COLOR_ATTACHMENT23,

	/*(3.0) Framebuffer color attachment unit 24*/
	Color24 = GL_COLOR_ATTACHMENT24,

	/*(3.0) Framebuffer color attachment unit 25*/
	Color25 = GL_COLOR_ATTACHMENT25,

	/*(3.0) Framebuffer color attachment unit 26*/
	Color26 = GL_COLOR_ATTACHMENT26,

	/*(3.0) Framebuffer color attachment unit 27*/
	Color27 = GL_COLOR_ATTACHMENT27,

	/*(3.0) Framebuffer color attachment unit 28*/
	Color28 = GL_COLOR_ATTACHMENT28,

	/*(3.0) Framebuffer color attachment unit 29*/
	Color29 = GL_COLOR_ATTACHMENT29,

	/*(3.0) Framebuffer color attachment unit 30*/
	Color30 = GL_COLOR_ATTACHMENT30,

	/*(3.0) Framebuffer color attachment unit 31*/
	Color31 = GL_COLOR_ATTACHMENT31,

	/*(3.0) Framebuffer depth attachment type*/
	Depth = GL_DEPTH_ATTACHMENT,

	/*(3.0) Framebuffer stencil attachment type*/
	Stencil = GL_STENCIL_ATTACHMENT,
};

/*(3.0) GLAD framebuffer attached image object type enumerator*/
enum class Framebuffers::AttachmentType : GLenum
{
	/*(3.0) No attached unit*/
	None = GL_NONE,

	/*(3.0) Attached unit is texture object*/
	Texture = GL_TEXTURE,

	/*(3.0) The default framebuffer is used for drawing*/
	Default = GL_FRAMEBUFFER_DEFAULT,

	/*(3.0) Attached unit is renderbuffer object*/
	Renderbuffer = GL_RENDERBUFFER,
};

/*(3.0) GLAD framebuffer completeness status enumerator*/
enum class Framebuffers::CompletenessStatus : GLenum
{
	/*(3.0) Returned if the specified framebuffer is the default read or draw framebuffer, but the default framebuffer does not exist*/
	Undefined = GL_FRAMEBUFFER_UNDEFINED,

	/*(3.0) Returned if the specified framebuffer is complete*/
	Complete = GL_FRAMEBUFFER_COMPLETE,

	/*(3.0) Returned if any of the framebuffer attachment points are framebuffer incomplete*/
	IncompleteAttachment = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,

	/*(3.0) Returned if the framebuffer does not have at least one image attached to it*/
	IncompleteMissingAttachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,

	/*(3.0) Returned if the value of attachment object type is <None> for any color attachment point(s) named by draw buffer*/
	IncompleteDrawBuffer = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,

	/*(3.0) Returned read buffer is not <None>, and if the value of attachment object type is <None> for the color attachment point named by read buffer*/
	IncompleteReadBuffer = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,

	/*(3.0) Returned if the combination of internal formats of the attached images violates an implementation-dependent set of restrictions*/
	Unsupported = GL_FRAMEBUFFER_UNSUPPORTED,

	/*(3.0) Returned if the number of samples is not the same for all attached renderbuffers*/
	IncompleteMultisample = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,

#ifdef YAGLPP_VERSION_3_2
	/*(3.2) Returned if any framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target*/
	IncompleteLayerTargets = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS,
#endif // #ifdef YAGLPP_VERSION_3_2
};

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
void Framebuffers::blit_framebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLuint read, GLuint draw, GLenum mask, GLenum filter)
{
	// READ FRAMEBUFFER OBJECT IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_READ_FRAMEBUFFER_BINDING, read));

	// DRAW FRAMEBUFFER OBJECT IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_DRAW_FRAMEBUFFER_BINDING, draw));

	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, (GLbitfield)mask, (GLenum)filter);
	YAGLPP_GLAD_ERROR; //works only with GL_READ_FRAMEBUFFER
}

GLenum Framebuffers::check_framebuffer_status(GLenum target, GLenum binding)
{
	// FRAMEBUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	return glCheckFramebufferStatus(target);
}

void Framebuffers::framebuffer_renderbuffer(GLenum target, GLenum binding, GLenum attachment, GLuint renderbuffer)
{
	// FRAMEBUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// RENDERBUFFER OBJECT IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_RENDERBUFFER_BINDING, renderbuffer));

	glFramebufferRenderbuffer(target, attachment, GL_RENDERBUFFER, renderbuffer);
	YAGLPP_GLAD_ERROR;
}

void Framebuffers::framebuffer_texture_1d(GLenum target, GLenum binding, GLenum attachment, GLuint texture, GLint level)
{
	// FRAMEBUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// 1D TEXURE OBJECT IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_TEXTURE_BINDING_1D, texture));

	glFramebufferTexture1D(target, attachment, GL_TEXTURE_1D, texture, level);
	YAGLPP_GLAD_ERROR;
}

void Framebuffers::framebuffer_texture_2d(GLenum target, GLenum binding, GLenum attachment, GLuint texture, GLenum textarget, GLenum texbinding, GLint level)
{
	// FRAMEBUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// 2D TEXURE OBJECT IS UNBOUND
	YAGLPP_ASSERT(object_binding(texbinding, texture));

	glFramebufferTexture2D(target, attachment, textarget, texture, level);
	YAGLPP_GLAD_ERROR;
}

void Framebuffers::framebuffer_texture_3d(GLenum target, GLenum binding, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
	// FRAMEBUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// 3D TEXURE OBJECT IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_TEXTURE_BINDING_3D, texture));

	glFramebufferTexture3D(target, attachment, GL_TEXTURE_3D, texture, level, layer);
	YAGLPP_GLAD_ERROR;
}

void Framebuffers::framebuffer_texture_layer(GLenum target, GLenum binding, GLenum attachment, GLuint texture, GLenum texbinding, GLint level, GLint layer)
{
	// FRAMEBUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// TEXURE OBJECT IS UNBOUND
	YAGLPP_ASSERT(object_binding(texbinding, texture));

	glFramebufferTextureLayer(target, attachment, texture, level, layer);
	YAGLPP_GLAD_ERROR;
}

GLint Framebuffers::get_framebuffer_attachment_parameter(GLenum target, GLenum binding, GLenum attachment, GLenum pname)
{
	// FRAMEBUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	GLint iResult;
	glGetFramebufferAttachmentParameteriv(target, attachment, pname, &iResult);
	YAGLPP_GLAD_ERROR;
	return iResult;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void Framebuffers::blit_framebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLuint read, GLuint draw, GLenum mask, GLenum filter)
{
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, (GLbitfield)mask, (GLenum)filter);
}

inline GLenum Framebuffers::check_framebuffer_status(GLenum target, GLenum binding)
{
	return glCheckFramebufferStatus(target);
}

inline void Framebuffers::framebuffer_renderbuffer(GLenum target, GLenum binding, GLenum attachment, GLuint renderbuffer)
{
	glFramebufferRenderbuffer(target, attachment, GL_RENDERBUFFER, 0);
}

inline void Framebuffers::framebuffer_texture_1d(GLenum target, GLenum binding, GLenum attachment, GLuint texture, GLint level)
{
	glFramebufferTexture1D(target, attachment, GL_TEXTURE_1D, texture, level);
}

inline void Framebuffers::framebuffer_texture_2d(GLenum target, GLenum binding, GLenum attachment, GLuint texture, GLenum textarget, GLenum texbinding, GLint level)
{
	glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

inline void Framebuffers::framebuffer_texture_3d(GLenum target, GLenum binding, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
	glFramebufferTexture3D(target, attachment, GL_TEXTURE_3D, texture, level, layer);
}

inline void Framebuffers::framebuffer_texture_layer(GLenum target, GLenum binding, GLenum attachment, GLuint texture, GLenum texbinding, GLint level, GLint layer)
{
	glFramebufferTextureLayer(target, attachment, texture, level, layer);
}

inline GLint Framebuffers::get_framebuffer_attachment_parameter(GLenum target, GLenum binding, GLenum attachment, GLenum pname)
{
	GLint i; glGetFramebufferAttachmentParameteriv(target, attachment, pname, &i); return i;
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Framebuffers::framebuffer_texture(GLenum target, GLenum binding, GLenum attachment, GLuint texture, GLenum textarget, GLenum texbinding, GLint level)
{
	// FRAMEBUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// 2D TEXURE OBJECT IS UNBOUND
	YAGLPP_ASSERT(object_binding(texbinding, texture));

	glFramebufferTexture(target, attachment, texture, level);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Framebuffers::framebuffer_texture(GLenum target, GLenum binding, GLenum attachment, GLuint texture, GLenum textarget, GLenum texbinding, GLint level)
{
	glFramebufferTexture(target, attachment, texture, level);
}
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_INLINE_IMPLEMENTATION)
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_0
#endif // #ifndef YAGLPP_FRAMEBUFFERS_H
