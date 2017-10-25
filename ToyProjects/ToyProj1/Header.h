#pragma once

#ifdef TOYPROJ1_EXPORTS  
#define TOY_API __declspec(dllexport)   
#else  
#define TOY_API __declspec(dllimport)
#endif  

extern "C" TOY_API int run();