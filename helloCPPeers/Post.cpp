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
#include <string>
#include <stdexcept>
#include <sstream>
#include "Post.h"

using std::string;
using std::vector;

Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

vector<string> Post::findTags() {
	std::istringstream iss(postText);
	string tag;
	vector<string> allTags;
	bool end = true;
	
	while(!iss.eof())
	{
		iss >> tag;
		if(tag.at(0) == '#')
		{
			if(tag.length() != 1)
			{
				for(int x = 1; x < tag.length(); x++)
				{
					if((tag.at(x) < 65 || tag.at(x) > 90) && (tag.at(x) > 122 || tag.at(x) < 97))
					{
						end = true;
						if(x != tag.length() - 1)
						{
							for(int y = x + 1; y < tag.length(); y++)
								if((tag.at(y) >= 65 && tag.at(y) <= 90) || (tag.at(y) <= 122 && tag.at(y) >= 97))
								{
									end = false;
									break;
								}
						}
					
						if(end)
						{
							tag = tag.substr(0, x);
							break;
						}
					}
					tag.at(x) = std::tolower(tag.at(x));
				}
			}
			allTags.push_back(tag);
		}
	}
	return allTags;
}
