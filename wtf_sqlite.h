#ifndef WTF_SQLITE_H
#define WTF_SQLITE_H

#include <sqlite3.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

bool InitDatabase(const char *filename);
void CloseDatabase(void);

bool ExecuteStatement(const char *sql);
bool PrepareStatement(const char *sql);
bool StepStatement(void);
void FinaliseStatement(void);

bool BindNull(int idx);
bool BindInt(int idx, int value);
bool BindDouble(int idx, double value);
bool BindText(int idx, const char *value);

int CountColumns(void);
int GetColumnInt(int idx);
double GetColumnDouble(int idx);
const unsigned char *GetColumnText(int idx);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // WTF_SQLITE_H
