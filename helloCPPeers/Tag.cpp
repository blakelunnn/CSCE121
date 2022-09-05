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
#include "Tag.h"

using std::string;
using std::vector;

Tag::Tag(string tag): tagName(tag), tagPosts({}) /* TODO(student): initialize */ {
	if(tagName.length() < 2)
		throw std::invalid_argument("Length too short");
	if(tagName.at(0) != '#')
		throw std::invalid_argument("First character is not a \"#\"");
	if(tagName.at(1) > 122 || tagName.at(1) < 97)
		throw std::invalid_argument("The second character is not from \"a\" - \"z\"");
	for(int x = 0; x < tagName.length(); x++)
		if(tagName.at(x) >= 65 && tagName.at(x) <= 90)
			throw std::invalid_argument("Cannot contain uppercase letters");
}

string Tag::getTagName() {
	return tagName;
}

vector<Post*>& Tag::getTagPosts() {
	return tagPosts;
}

void Tag::addTagPost(Post* post) {
	if(post == nullptr)
		throw std::invalid_argument("tag post is nullptr");
	
	tagPosts.push_back(post);
}
