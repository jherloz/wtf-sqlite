#include "wtf_sqlite.h"

#include <stdlib.h>

static sqlite3 *SQLITE_DATABASE;
static sqlite3_stmt *SQLITE_STATEMENT;

bool InitDatabase(const char *filename) {
	if (sqlite3_open(filename, &SQLITE_DATABASE) == SQLITE_OK) {
		ExecuteStatement("PRAGMA foreign_keys = ON;");

		return true;
	}

	return false;
}

void CloseDatabase(void) {
	if (SQLITE_DATABASE) {
		FinaliseStatement();
		sqlite3_close(SQLITE_DATABASE);
	}
}

bool ExecuteStatement(const char *sql) {
	return sqlite3_exec(SQLITE_DATABASE, sql, NULL, NULL, NULL) == SQLITE_OK;
}

bool PrepareStatement(const char *sql) {
	FinaliseStatement();

	return sqlite3_prepare_v2(SQLITE_DATABASE, sql, -1, &SQLITE_STATEMENT, NULL) == SQLITE_OK;
}

bool StepStatement(void) {
	return sqlite3_step(SQLITE_STATEMENT) == SQLITE_ROW;
}

void FinaliseStatement(void) {
	if (SQLITE_STATEMENT) {
		sqlite3_finalize(SQLITE_STATEMENT);
		SQLITE_STATEMENT = NULL;
	}
}

bool BindNull(int idx) {
	return sqlite3_bind_null(SQLITE_STATEMENT, idx) == SQLITE_OK;
}

bool BindInt(int idx, int value) {
	return sqlite3_bind_int(SQLITE_STATEMENT, idx, value) == SQLITE_OK;
}

bool BindDouble(int idx, double value) {
	return sqlite3_bind_double(SQLITE_STATEMENT, idx, value) == SQLITE_OK;
}

bool BindText(int idx, const char *value) {
	return sqlite3_bind_text(SQLITE_STATEMENT, idx, value, -1, SQLITE_TRANSIENT) == SQLITE_OK;
}

int CountColumns(void) {
	return sqlite3_column_count(SQLITE_STATEMENT);
}

int GetColumnInt(int idx) {
	return sqlite3_column_int(SQLITE_STATEMENT, idx);
}

double GetColumnDouble(int idx) {
	return sqlite3_column_double(SQLITE_STATEMENT, idx);
}

const unsigned char *GetColumnText(int idx) {
	return sqlite3_column_text(SQLITE_STATEMENT, idx);
}
