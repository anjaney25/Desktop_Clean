#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

/*function... might want it in some class?*/
vector< pair<int, string> > v;
bool sortinrev(const pair<int,string> &a, const pair<int,string> &b)
{
       return (a.first > b.first);
}
template <typename T>
  string NumberToString ( T Number )
  {
     ostringstream ss;
     ss << Number;
     return ss.str();
  }
int get_file_size(string filename) // path to file
{
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(),"rb");
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}
wstring s2ws(const string& str)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo( size_needed, 0 );
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}
int GetFileSize(wstring const &path) {

    WIN32_FIND_DATAW data;
    HANDLE h = FindFirstFileW(path.c_str(), &data);
    if (h == INVALID_HANDLE_VALUE)
        return -1;

    FindClose(h);

    return data.nFileSizeLow | (int)data.nFileSizeHigh << 32;
}
int getdir (string dir)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        //cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    string s1;
    //int count=0;
    while ((dirp = readdir(dp)) != NULL){
        if(dirp->d_name[0] != '.'){
            s1 = dir + "\\" + dirp->d_name;
            //cout << s1 << endl;
            int si = GetFileSize(s2ws(s1));
            int fi = (si/1000000);
            string s2 = NumberToString(si);
            //cout << v.size() << " ";

            if(si==0){
                getdir(s1);
            }
            else {
                if(v.size() < 12) v.push_back(make_pair(fi, s1));
                else{
                        v[11] = (make_pair(fi, s1));
                        sort(v.begin(), v.end(), sortinrev);
                }
            }
        }
    }
    closedir(dp);
    return 0;
}
int clean(string dir, string newdir){
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
                    //cout << name.substr(f+1) << "  " << name << endl;
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
                if ( result == 0 )
                    cout << ( "File successfully renamed \n" );
                else
                    cout << ( "Error in transferring file \n" );
            }
        }
    }

        return 0;
}

int main()
{

    string drv = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int d=0; d<26; d++){
      string Letter(1,drv[d]);
    string s = Letter + ":";
    //cout << s << " ";
    string dir = string(s);
    vector<string> files = vector<string>();
    getdir(dir);
    }
    if(v.size() && v.size() < 10)
        for(int j=0; j<v.size(); j++) cout << v[j].first << " " << v[j].second << endl;
    else if(v.size >= 10)
        for(int j=0; j<10; j++) cout << v[j].first << " " << v[j].second << endl;
    else cout << "Wrong Path" << endl;

    string s2 = "C:\\Users\\Anjaney Sharma\\Desktop\\code\\first\\innovaccer\\abcd";
    string s3 = "C:\\Users\\Anjaney Sharma\\Desktop\\code\\first\\innovaccer\\efgh";
    clean(s2, s3);
    return 0;
}
