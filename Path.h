#ifndef PATH_H
#define PATH_H

using namespace std;
namespace fs = std::filesystem;

class Path {
	private:
		fs::path absolutePath;
        bool isDirectory = false;
        fs::path startAddPath = "Map";
	public:
		Path(fs::path absolutePath) {
            this->absolutePath = absolutePath;
            if (fs::is_directory(absolutePath)) {
                this->isDirectory = true;
            }
        }
        Path() {}
		
        fs::path GetAbsolutePath() {
            return absolutePath;
        }

		bool IsDirectory() {
            return isDirectory;
        }

        void AddPathToMap() {
            if (isDirectory) {
                fs::path addPath = startAddPath;
                addPath += absolutePath;
                cout << addPath << endl;
                fs::create_directories(addPath);
            }
            else {
                fs::path directoryPath = startAddPath;
                fs::path original = absolutePath;
                directoryPath += original.remove_filename();
                fs::create_directories(directoryPath);

                fs::path fStreamPath = startAddPath;
                fStreamPath += absolutePath;
                ofstream outFile;
                outFile.open(fStreamPath);
                if (!outFile.is_open()) {
                    throw std::invalid_argument("Unable to update Map directory");
                }
                outFile.close();
            }
            return;
        }

};
#endif