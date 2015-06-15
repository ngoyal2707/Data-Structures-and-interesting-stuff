
// Author: ngoyal2707

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <vector>

using namespace std;



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
        while(i<s.length() && curr->child[s[i]-'a']!=NULL ){
            curr=curr->child[s[i]-'a'];
            curr->wordCount++;
            i++;
        }
        while(i<s.length()){
            curr->child[s[i]-'a']=new TrieNode();
            curr->wordCount++;
            curr=curr->child[s[i]-'a'];
            i++;
        }
        curr->isLeaf=1;
        curr->wordIndexDictionary=wordIndex;
    }

    // Returns if the word is in the trie.
    bool search(string key) {
        TrieNode *curr=root;
        int i=0;
        while(i<key.length() && curr->child[key[i]-'a']!=NULL){
            curr=curr->child[key[i]-'a'];
            i++;
        }
        if(i==key.length() && curr->isLeaf)
            return true;
        return false;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode *curr=root;
        int i=0;
        while(i<prefix.length() && curr->child[prefix[i]-'a']!=NULL){
            curr=curr->child[prefix[i]-'a'];
            i++;
        }
        if(i==prefix.length())
            return true;
        return false;
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
    
private:
    TrieNode* root;
    int visited[100][100];
    
};

int main(int argc, char const *argv[])
{
	Solution s;
	// const char *boardChars[]={"oaan","etae","ihkr","iflv"};
	vector<vector<char> > board;
	std::vector<char> v;
	// v.push_back('o');
	// v.push_back('a');
	// v.push_back('a');
	// v.push_back('n');
	// board.push_back(v);

	// v.clear();
	// v.push_back('e');
	// v.push_back('t');
	// v.push_back('a');
	// v.push_back('e');
	// board.push_back(v);
	
	// v.clear();
	// v.push_back('i');
	// v.push_back('h');
	// v.push_back('k');
	// v.push_back('r');
	// board.push_back(v);

	// v.clear();
	// v.push_back('i');
	// v.push_back('f');
	// v.push_back('l');
	// v.push_back('v');
	// board.push_back(v);

	v.push_back('a');
	v.push_back('a');
	v.push_back('a');
	board.push_back(v);
	v.push_back('a');
	v.push_back('a');
	v.push_back('a');
	board.push_back(v);
	v.push_back('a');
	v.push_back('a');
	v.push_back('a');
	board.push_back(v);

	// const char *dictionaryChar[]={"a"};
	std::vector<string> dictionary;
	// (dictionaryChar,dictionaryChar+2);
	dictionary.push_back(string("aaaaaaaaa"));

	vector<string> result=s.findWords(board,dictionary);
	for(int i=0;i<result.size();i++){
		cout<<result[i]<<"\n";
	}
	return 0;
}