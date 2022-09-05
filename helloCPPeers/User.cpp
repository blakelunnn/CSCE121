/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include "User.h"

using std::string;
using std::vector;

User::User(string user): userName(user), userPosts({}) /* TODO(student): initialize */ {
  // TODO(student): implement constructor checks
	if(userName == "")
		throw std::invalid_argument("Empty name");
	
	if(userName.at(0) > 122 || userName.at(0) < 97)
		throw std::invalid_argument("Name does not start with letter \"a\" - \"z\"");
		
	for(int x = 0; x < userName.length(); x++)
		if(userName.at(x) >= 65 && userName.at(x) <= 90)
			throw std::invalid_argument("Cannot contain uppercase letters");
}

string User::getUserName() {
	return userName;
}

vector<Post*>& User::getUserPosts() {
	return userPosts;
}

void User::addUserPost(Post* post) {
	if(post == nullptr)
		throw std::invalid_argument("name is nullptr");
	
	userPosts.push_back(post);
}
