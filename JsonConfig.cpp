// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	class JsonConfig {
	private:
		nlohmann::json jsonFile;
		const string configFileName = "punclev-utils.json";
	public:
		void loadConfig() {
			zoptions->ChangeDir(DIR_SYSTEM);
			zFILE_VDFS* originFile = new zFILE_VDFS(configFileName);

			if (!originFile->Exists()) {
				delete originFile;
				return;
			}

			originFile->Open(false);

			zSTRING line, buffer;
			do {
				originFile->Read(line);
				buffer += line;
			} while (!originFile->Eof());

			originFile->Close();
			jsonFile = nlohmann::json::parse(buffer.ToChar());
		}

		nlohmann::json* lootTable(const char* name) {
			if (!jsonFile["loot-tables"].is_object()) {
				return nullptr;
			}

			if (!jsonFile["loot-tables"][name].is_array()) {
				return nullptr;
			}

			return &jsonFile["loot-tables"][name];
		}
	};
}