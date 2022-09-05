/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ifstream;

Network::Network() {
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName) {
	ifstream ifs(fileName);
	
	if(!ifs.is_open())
		throw std::invalid_argument("Unable to open file");
	if(fileName.find(".txt") == string::npos)
		throw std::runtime_error("Incorrect file type (not .txt)");
	
	while(!ifs.eof())
	{
		string indicator = "";
		string userName = "";
		unsigned int postId = 0;
		string postText = "";
		ifs >> indicator;
		if(indicator == "")
			break;
		if(indicator == "User")
		{
			ifs >> userName;
			try
			{
				addUser(userName);
			}
			catch(std::invalid_argument& excpt)
			{
				throw std::runtime_error("Error Occured");
			}
		}
		else if(indicator == "Post")
		{
			ifs >> postId;
			ifs >> userName;
			getline(ifs, postText);
			try
			{
				addPost(postId, userName, postText);
			}
			catch(std::invalid_argument& excpt)
			{
				throw std::runtime_error("Error Occured");
			}
		}
		else
			throw std::runtime_error("Invalid file format");
	}
}

void Network::addUser(string userName) {
	for(int x = 0; x < userName.length(); x++)
		userName.at(x) = std::tolower(userName.at(x));
	for(int x = 0; x < users.size(); x++)
		if(userName == users[x]->getUserName())
			throw std::invalid_argument("Name not unique");
			
	User* name = new User(userName);	
	users.push_back(name);
	cout << "Added User " << userName << endl;
}

void Network::addPost(unsigned int postId, string userName, string postText) {
	for(int x = 0; x < posts.size(); x++)
		if(postId == posts[x]->getPostId())
			throw std::invalid_argument("Post Id Already Exists");
	
	string temp = userName;
	bool invalid = true;
	for(int x = 0; x < temp.size(); x++)
		if(temp.at(x) <= 90 && temp.at(x) >= 65)
			temp.at(x) = temp.at(x) + 32;
			
	User* correspondingUser;
	for(int x = 0; x < users.size(); x++)
	{
		User* tempUser = users.at(x);
		if(tempUser->getUserName() == temp)
		{
			invalid = false;
			correspondingUser = tempUser;
		}
	}
	
	if(invalid)
		throw std::invalid_argument("User Does Not Exist");
	
	Post* post = new Post(postId, userName, postText);
	posts.push_back(post);
	correspondingUser->addUserPost(post);
	vector<string> tagsOfPost = post->findTags();
	
	for(int x = 0; x < tagsOfPost.size(); x++)
	{
		try
		{
			bool newTag = true;
			for(int y = 0; y < tags.size(); y++)
				if(tagsOfPost.at(x) == (tags.at(y))->getTagName())
				{
					newTag = false;
					(tags.at(y))->addTagPost(post);
				}
			if(newTag)
			{
				Tag* tag = new Tag(tagsOfPost.at(x));
				tag->addTagPost(post);
				tags.push_back(tag);
			}
		}
		catch(std::invalid_argument& excpt)
		{
			continue;
		}
	}

	cout << "Added Post " << postId << " by " << userName << endl;
}

vector<Post*> Network::getPostsByUser(string userName) {
	if(userName == "")
		throw std::invalid_argument("Didn't give a User Name");
	bool found = false;
	for(int x = 0; x < users.size(); x++)
		if(userName == users[x]->getUserName())
			found = true;
	if(!found)
		throw std::invalid_argument("No such User Name Exists");
	
	int indexOfUser = 0;
	for(int x = 0; x < users.size(); x++)
		if(userName == users[x]->getUserName())
		{
			indexOfUser = x;
			break;
		}
	return users[indexOfUser]->getUserPosts();
}

vector<Post*> Network::getPostsWithTag(string tagName) {
	if(tagName == "")
		throw std::invalid_argument("Didn't give a Tag");
	bool found = false;
	for(int x = 0; x < tags.size(); x++)
		if(tagName == tags[x]->getTagName())
			found = true;
	if(!found)
		throw std::invalid_argument("No such Tag Exists");
		
	int indexOfTag = 0;
	for(int x = 0; x < tags.size(); x++)
		if(tagName == tags[x]->getTagName())
		{
			indexOfTag = x;
			break;
		}
	return tags[indexOfTag]->getTagPosts();
}

vector<string> Network::getMostPopularHashtag() {
	vector<string> popularTags;
	
	if(tags.size() == 0)
		return popularTags;
	
	popularTags.push_back((*tags.at(0)).getTagName());
	int max = (*tags.at(0)).getTagPosts().size();
	
	for(int x = 1; x < tags.size(); x++)
	{
		int temp = (*tags.at(x)).getTagPosts().size();
		if(temp > max)
		{
			popularTags.clear();
			popularTags.push_back((*tags.at(x)).getTagName());
			max = temp;
		}
		else
			if(temp == max)
				popularTags.push_back((*tags.at(x)).getTagName());
	}

	return popularTags;
}


/**
  * Destructor
  * Do not change; already implemented.
  */
Network::~Network() {
  for (unsigned int i = 0; i < users.size(); ++i) {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i) {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i) {
    delete posts.at(i);
  }
}
