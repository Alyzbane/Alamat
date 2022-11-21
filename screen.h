#ifndef SCREEN_H
#define SCREEN_H

#if defined (WIN32) || defined(_WIN32) || defined(__NT__) || defined(_WIN64)
void ClearScreen(void);

#elif __LINUX__
void ClearScreen(void);

#else 
void ClearScreen(void);
#endif

#endif
