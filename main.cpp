#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
bool start();
void test();
void get5words();
void get6words();
bool fill_vec(vector<string>& avalable);
bool judge(string guess, vector<string>& avalable);
string make_guess(int &size);
void get_colors(string guess, vector<char>& result);
void check_for_doubles(string guess, vector<char>& result);
void eliminate_words(vector<char>& result, string guess, vector<string>& avalable);
bool is_valid(string guess, vector<char> results, string word);
void play();

int main(){
  play();
  return 0;
}

void play(){
  bool done = false;
  char play;
  int size=0;
  string file;
  while(!done){
    bool win = false;
    vector<string> avalable;
    string guess;
    if(!start()) return;
    if(!fill_vec(avalable)) return;
    for(int i = 0; i < 10;++i){
      guess = make_guess(size);
      if(guess=="go1"){win=true; break;}
      if(judge(guess, avalable)){
        win = true;
        i = 10;
      };
    }
    if(win) cout<<"You Win!!"<<endl;
    else cout<<"you lose"<<endl;
    bool valid = false;
    while(!valid){
      cout<<"do you want to play again?('y' or 'n')";
      cin>>play;
      if(play=='y') valid = true;
      else if(play=='n') {valid = true; done = true;}
      else cout << "not a valid input..."<<endl;
    }

  }
}

bool judge(string guess, vector<string>& avalable){
  vector<char> result;
  get_colors(guess, result);
  check_for_doubles(guess, result);
  eliminate_words(result, guess, avalable);
  if(avalable.size()==2) return true;
  return false;
}


void eliminate_words(vector<char>& result, string guess, vector<string>& avalable){
  char color;
  string tmp;

  ofstream out;
  out.open("stillAvalable.txt");
  if(!out){
    cout << "could not open file"<<endl;
  }
  else{
    while(!avalable.empty()){
      tmp = avalable.back();
      avalable.pop_back();
      if(is_valid(guess, result, tmp)) out<<tmp<<endl;
    }
  }
  out.close();
  fill_vec(avalable);
}


bool is_valid(string guess, vector<char> results, string word){
  for(int i = 0; i < 5; i++){
    if(results[i]=='g'){
      if(guess[i]!=word[i]) return false;
    }
    else if(results[i]=='y'){
      bool is_in_word = false;
      if(guess[i]==word[i]) return false;
      for(int j=0; j<5;j++){
        if(j!=i){
          if(guess[i]==word[j]) is_in_word = true;
        }
      }
      if(!is_in_word) return false;
    }
    else if(results[i]=='b'){
      for(int j=0; j<5;j++){
        if(guess[i]==word[j]) return false;
      }
    }
    else if(results[i]=='i'){
      if(guess[i]==word[i]) return false;
    }
  }
  return true;
}


void check_for_doubles(string guess, vector<char>& result){

  for(int i = 0; i < 4; i++){
    for(int j = i+1; j < 5; j++){
      if(guess[i] == guess[j]){

        if(result[i]=='g'&&result[j]=='b'){
          result[j]='i';
        }
        if(result[j]=='g'&&result[i]=='b'){
          result[i]='i';
        }
        if(result[i]=='y'&&result[j]=='b'){
          result[j]='i';
        }
        if(result[j]=='y'&&result[i]=='b'){
          result[i]='i';
        }
      }
    }
  }
}


void get_colors(string guess, vector<char>& result){
  char tmp;
  for(int i=0;i<5;i++){
    bool done = false;
    while(!done){
      cout<<"What was the result for the letter "<<guess[i]<<":  ";
      cin>>tmp;
      if(tmp=='g' || tmp=='y' || tmp=='b') done = true;
      else cout<<"invalid input."<<endl;
    }
    result.push_back(tmp);
  }
}


string make_guess(int &size){
  bool done = false;
  string guess;
  while(!done){
    cout<< "Guess a five letter word:    ";
    cin >> guess;
    if(guess.length()!=5 && guess!="go1") cout<<"Word is invalid.\n";
    else done = true;
  }
  return guess;
}


bool fill_vec(vector<string>& avalable){
  ifstream ins;
  string word;
  ins.open("stillAvalable.txt");
  if(!ins){
    cout << "could not fill vector"<<endl;
    return false;
  }
  while(!ins.eof()){
    getline(ins, word);
    avalable.push_back(word);
  }
  ins.close();
  return true;
}

bool start(){
  ifstream inp;
  ofstream out;
  string word;
  inp.open("FiveWords.txt");
  if(!inp) {
    cout << "Cannot open input file.\n";
    return false;
  }
  out.open("stillAvalable.txt");
  if(!out) {
    cout << "Cannot open output file.\n";
    return false;
  }
  while(!inp.eof()){
    getline(inp, word);
    out << word << endl;
  }

  inp.close();
  out.close();
  return true;
}














void get5words(){
ifstream inp;
ofstream out;
string word;
inp.open("words_alpha.txt");
if(!inp) {
  cout << "Cannot open input file.\n";
  //return 1;
}

out.open("FiveWords.txt");
if(!out) {
  cout << "Cannot open input file.\n";
  //return 1;
}
while(!inp.eof()){
  getline(inp, word);
  if(word.length()==6) out << word << endl;
}
inp.close();
}


void get6words(){
ifstream inp;
ofstream out;
string word;
inp.open("words_alpha.txt");
if(!inp) {
  cout << "Cannot open input file.\n";
  //return 1;
}

out.open("SixWords.txt");
if(!out) {
  cout << "Cannot open input file.\n";
  //return 1;
}
while(!inp.eof()){
  getline(inp, word);
  if(word.length()==7) out << word << endl;
}
inp.close();
}


void test(){
  ifstream inp;
  string x;
  inp.open("stillAvalable.txt");
  if(!inp) {
    cout << "Cannot open output file.\n";
  }
  else{
    vector<string> v;
    while(!inp.eof()){
      getline(inp, x);
      v.push_back(x);
    }
    for(int i = 0; i<v.size(); ++i)cout << i << "  "<< v[i]<<endl;
  }
}
