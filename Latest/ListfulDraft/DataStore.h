//@author A0110670W
#ifndef DATASTORE_H
#define DATASTORE_H

#include "Entry.h"

class DataStore {
	private:
		std::vector <Entry> _dataBase;
		std::vector <std::vector <Entry>> _undoData;
		std::vector <std::vector <Entry>> _redoData;
		std::vector <std::vector <Entry>> _undoTempData;
		std::vector <std::vector <Entry>> _redoTempData;
		std::vector <std::string> _undoActionLog;
		std::vector <std::string> _redoActionLog;

		std::vector <Entry> _tempDataBase;
		std::vector <int> _tempIndexList;

		Entry _tempEntry;
		Entry _emptyEntry;
		std::string _fileName;

	public:
		DataStore () {};
		void init(std::string);

		void updateFile(DataStore &);
		void savePrevFile();		

		bool undoData(DataStore &, std::ostringstream &);
		bool redoData(DataStore &, std::ostringstream &);
		void savePrevAction(std::string);
		void clearData(std::ostringstream &, std::ostringstream &, std::ostringstream &);
		
		std::vector <Entry> &getData();
		std::vector <int> &getTempIndexList();
		std::vector <Entry> &getTempData();		
	
		std::vector <std::string> &getUndoActionLog();
		std::vector <std::string> &getRedoActionLog();

		Entry &getEntry(int);
		Entry &get_tempEntry();
		Entry &get_emptyEntry();
};

#endif