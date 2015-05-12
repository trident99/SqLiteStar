#ifndef SQLITE3_GLOBAL_H
#define SQLITE3_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef SQLITE3_LIB
# define SQLITE3_EXPORT Q_DECL_EXPORT
#else
# define SQLITE3_EXPORT Q_DECL_IMPORT
#endif

#endif // SQLITE3_GLOBAL_H
