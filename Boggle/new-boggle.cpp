
// Author: ngoyal2707

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <cstring>

using namespace std;

#define MAX_BOARD_SIZE 1100

int BOARD_SIZE;
class TrieNode {
public:
    int isLeaf;
    int wordIndexDictionary;
    int wordCount;
    TrieNode *child[26];
    TrieNode() {
        isLeaf=0;
        wordCount=0;
        for(int i=0;i<26;i++){
            child[i]=NULL;
        }
    }

};

class Solution {
public:
    Solution() {
        root = new TrieNode();
    }

    // void printTrie(){

    // }
    // Inserts a word into the trie.
    void insert(string s,int wordIndex) {
        TrieNode* curr=root;
        int i=0;
        std::transform(s.begin(),s.end(),s.begin(),::tolower);
        while(i<s.length()){
            int index=-1;
            if(('a'<=s[i])&&('z'>=s[i]))
                index=s[i]-'a';
            
            if(index==-1){
                i++;
                continue;
            }
            if(curr->child[index]==NULL)
                break;

            curr=curr->child[index];
            curr->wordCount++;
            i++;
        }
        while(i<s.length()){
            int index=-1;
            if(('a'<=s[i])&&('z'>=s[i]))
                index=s[i]-'a';
            // else if(('A'<=s[i])&&('Z'>=s[i]))
            //     index=s[i]-'A';
            if(index==-1){
                i++;
                continue;
            }

            curr->child[index]=new TrieNode();
            curr->wordCount++;
            curr=curr->child[index];
            i++;
        }
        curr->isLeaf=1;
        curr->wordIndexDictionary=wordIndex;
    }


    int findWordsRecur(vector<vector<char> >& board, int i,int j,int rows, int cols,TrieNode *curr,vector<string> &result,vector<string> &dictionary){
        int foundWords=0;
        if(curr==NULL)
            return 0; 
		if(curr->isLeaf){
			result.push_back(dictionary[curr->wordIndexDictionary]);
			curr->isLeaf=0;
			curr->wordCount--;
			foundWords++;
			if(curr->wordCount==0){
				curr=NULL;
				return 1;
			}
		}
		// cout<<i<<"\t"<<j<<"\n";
		visited[i][j]=1;
		int currCharIndex;
		if(i<rows-1) {
			currCharIndex=board[i+1][j]-'a';
			if(!visited[i+1][j])
				foundWords+=findWordsRecur(board,i+1,j,rows,cols,curr->child[currCharIndex],result,dictionary);
		}
		if(i>0) {
			currCharIndex=board[i-1][j]-'a';
			if(!visited[i-1][j])	
				foundWords+=findWordsRecur(board,i-1,j,rows,cols,curr->child[currCharIndex],result,dictionary);
		}
		if(j<cols-1) {
			currCharIndex=board[i][j+1]-'a';
			if(!visited[i][j+1])
				foundWords+=findWordsRecur(board,i,j+1,rows,cols,curr->child[currCharIndex],result,dictionary);
		}
		if(j>0) {
			currCharIndex=board[i][j-1]-'a';
			if(!visited[i][j-1])
				foundWords+=findWordsRecur(board,i,j-1,rows,cols,curr->child[currCharIndex],result,dictionary);
		}

        if(i<rows-1 && j<cols-1) {
            currCharIndex=board[i+1][j+1]-'a';
            if(!visited[i+1][j+1])
                foundWords+=findWordsRecur(board,i+1,j+1,rows,cols,curr->child[currCharIndex],result,dictionary);
        }
        if(i>0 && j< cols-1) {
            currCharIndex=board[i-1][j+1]-'a';
            if(!visited[i-1][j+1])    
                foundWords+=findWordsRecur(board,i-1,j+1,rows,cols,curr->child[currCharIndex],result,dictionary);
        }
        if(i>0 && j>0) {
            currCharIndex=board[i-1][j-1]-'a';
            if(!visited[i-1][j-1])
                foundWords+=findWordsRecur(board,i-1,j-1,rows,cols,curr->child[currCharIndex],result,dictionary);
        }
        if(i<rows-1 && j>0) {
            currCharIndex=board[i+1][j-1]-'a';
            if(!visited[i+1][j-1])
                foundWords+=findWordsRecur(board,i+1,j-1,rows,cols,curr->child[currCharIndex],result,dictionary);
        }



		curr->wordCount-=foundWords;
		if(curr->wordCount==0)
			curr=NULL;
		visited[i][j]=0;
		return foundWords;
    }

    vector<string> findWords(vector<vector<char> >& board, vector<string>& words) {
        
        for(int i=0;i<words.size();i++){
            insert(words[i],i);
            // cout<<words[i]<<"\n";
        }
        int m=board.size();
        int n=board[0].size();
        // cout<<m<<"\t"<<n;
        // bool **visited=new bool* [m];
        // for(int i=0;i<m;i++){
        // 	visited[i]=new bool[n];
        // }

        memset(visited,0,sizeof(visited));
        // cout<<"dsadsf";
        vector<string> result;
        for(int i=0;i<m;i++){
            for(int j=0;j<n && result.size()<words.size();j++){
            	visited[i][j]=1;
				int currCharIndex=board[i][j]-'a';
                findWordsRecur(board, i,j,m,n,root->child[currCharIndex],result,words);
                visited[i][j]=0;
            }
        }
        
        return result;
    }
    void printBoard(std::vector<std::vector<char> > board){
        int m=board.size();
        int n=board[0].size();
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                cout<<board[i][j]<<" ";
            }
            cout<<"\n";
        }
     }
private:
    TrieNode* root;
    int visited[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    
};

int main(int argc, char const *argv[])
{
	Solution s;
	// const char *boardChars[]={"oaan","etae","ihkr","iflv"};
	std::vector<char> v;
    BOARD_SIZE=atoi(argv[1]);
    cout<<BOARD_SIZE;
    vector<vector<char> > board(BOARD_SIZE,vector<char> (BOARD_SIZE));
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            board[i][j]=(rand()%26 +'a');
        }
    }
    // s.printBoard(board);

    clock_t begin = clock();
    std::vector<string> dictionary;
    string word;
    while(cin>>word){
        dictionary.push_back(word);
    }
	vector<string> result=s.   findWords(board,dictionary);
    clock_t end = clock();
    double elapsed_secs = double(end - begin)/CLOCKS_PER_SEC;

	for(int i=0;i<result.size();i++){
		// cout<<result[i]<<"\n";
	}
    cout<<"Found words:"<<result.size()<<"\n";
	cout<<"Time taken: "<<elapsed_secs<<"\n";
    return 0;
}