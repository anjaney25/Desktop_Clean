//Anjaney Sharma
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <Lmcons.h>
#include <bits/stdc++.h>
using namespace std;

vector< pair<unsigned long long int, string> > v;
bool sortinrev(const pair<int,string> &a, const pair<int,string> &b){
       return (a.first > b.first);
}

template <typename T>

wstring s2ws(const string& str)  //function to convert string to wstring
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo( size_needed, 0 );
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

unsigned long long int GetFileSize(wstring const &path) {  // function to get file size

    WIN32_FIND_DATAW data;
    HANDLE h = FindFirstFileW(path.c_str(), &data);
    if (h == INVALID_HANDLE_VALUE)
        return -1;

    FindClose(h);

    return data.nFileSizeLow | (unsigned long long int)data.nFileSizeHigh << 32;
}
int getlargefiles (string dir)  // function to get 10 files of largest sizes.
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        return errno;
    }

    string s1;
    while ((dirp = readdir(dp)) != NULL){
        if(dirp->d_name[0] != '.'){
            s1 = dir + "\\" + dirp->d_name;
            unsigned long long int si = GetFileSize(s2ws(s1));
            unsigned long long int fi = (si/1000000);

            if(si==0){
                getlargefiles(s1);
            }
            else {
                if(v.size() <= 10) v.push_back(make_pair(fi, s1));
                else{
                        v[10] = (make_pair(fi, s1));
                        sort(v.begin(), v.end(), sortinrev);
                }
            }
        }
    }
    closedir(dp);
    return 0;
}
int clean(string dir, string newdir){  // function to clean desktop
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    map<string, vector<string> > files;
    string name;
    string s1;
    while ((dirp = readdir(dp)) != NULL){
        s1 = dir + "\\" + dirp->d_name;
        if(dirp->d_name[0] != '.'){
            name = string(dirp->d_name);
            int f;
            for(f=name.size()-1; f>=0; f--) if(dirp->d_name[f] == '.') break;
            if(f!= -1 && GetFileSize(s2ws(s1)))
                files[name.substr(f+1)].push_back(name);
        }
    }
    map<string, vector<string> > :: iterator itr;
    int result;
    for(itr = files.begin(); itr != files.end(); itr++){
        if(itr->first != "lnk"){
        mkdir((newdir + "\\" + itr->first).c_str());
        for(vector<string> :: iterator it = (itr->second).begin(); it != (itr->second).end(); it++){
                result = rename((dir + "\\" + *it).c_str(), (newdir + "\\" + itr->first + "\\" + *it).c_str());
                if (result)
                    cout << ( "Error in transferring file " + *it);
            }
        }
    }

        return 0;
}

int main()
{
    //1st part of problem.
    string drv = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int d=0; d<26; d++){
      string Letter(1,drv[d]);
    string s = Letter + ":";
    string dir = string(s);
    vector<string> files = vector<string>();
    getlargefiles(dir);
    }
    if(v.size() && v.size() < 10){
            sort(v.begin(), v.end(), sortinrev);
        for(int j=0; j<v.size(); j++) cout << v[j].first << " " << v[j].second << endl;
    }
    else if(v.size() >= 10)
        for(int j=0; j<10; j++) cout << v[j].first << " " << v[j].second << endl;
    else cout << "Wrong Path" << endl;

//    2nd part of problem
      TCHAR name [ UNLEN + 1 ];
      DWORD size = UNLEN + 1;
      string user;
      if (GetUserName( (TCHAR*)name, &size )){
        user = string(name);
      }
      else{
        cout << "Please enter the user name.\n";
        cin >> user;
      }
      string desktop_path = "C:\\Users\\" + user + "\\Desktop";
        string documents_path = "C:\\Users\\" + user + "\\Documents";
        int err = clean(desktop_path, documents_path);
        if(err){ // this will run if the path of Desktop was wrong in above case.
            cout << "Please enter the folder path where Desktop and Documents folders are located.\n";
            char s2[100];
            cin.getline(s2, sizeof(s2));
            string desk = string(s2) + "\\Desktop";
            string docu = string(s2) + "\\Documents";
            clean(desk, docu);
        }
    return 0;
}
