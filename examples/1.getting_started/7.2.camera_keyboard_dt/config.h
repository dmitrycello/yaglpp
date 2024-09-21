// config.h
#define YAGLPP_CONFIG // Custom project config override
#define YAGLPP_IMPLEMENTATION // Comment this line if multiple YAGL++ inclusions

/*Define <CocoaChdirResources> pre-initialize GLFW hint*/
#define YAGLPP_COCOA_CHDIR_RESOURCES

/*Define <CocoaMenubar> pre-initialize GLFW hint*/
#define YAGLPP_COCOA_MENUBAR

/*Define <JoystickHatButtons> pre-initialize GLFW hint*/
#define YAGLPP_JOYSTICK_HAT_BUTTONS

/*Include the class properties along with existing getters and setters*/
#define YAGLPP_CLASS_PROPERTIES

/*Include all GLM library headers, slightly affects the compilation time*/
#define YAGLPP_GLM_HEADERS

/*Do not include main entry point into YAGL++ library*/
#define YAGLPP_NO_AFX_LAYOUT

/*Compile with the most recent GLFW nonlegacy library*/
#define YAGLPP_NO_GLFW_LEGACY

/*Define the minimum supported OpenGL context major version value, do not comment*/
#define YAGLPP_CONTEXT_VERSION_MAJOR 3

/*Define the minimum supported OpenGL context minor version value, do not comment*/
#define YAGLPP_CONTEXT_VERSION_MINOR 3

/*Define Assimp library file name, comment to exclude Assimp*/
#define YAGLPP_ASSIMP "assimp-vc142-mt.lib"

/*Define GLFW library file name, comment to exclude GLFW*/
#define YAGLPP_GLFW "glfw3.lib"

/*Include YAGL++*/
#include <yaglpp/glpp.h>
