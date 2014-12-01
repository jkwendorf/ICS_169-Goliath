// XMLTest.cpp : Defines the entry point for the console application.
//

/*
	To start off, make sure you have pugixml.hpp, pugixml.cpp, and pugiconfig.hpp (optional for now)
	included in your project.
*/
#include "stdafx.h"
#include "pugixml.hpp"
#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
	//This doc object is the root node for all nodes to be added in.
    pugi::xml_document doc;

	//This function load_file gets called and does two things:
	//1. Parses the tree and insert all of the children of the root node into the doc object.
	//2. Puts the result of the load function into result. The result basically returns if there was an error. *Don't worry about this part.
    pugi::xml_parse_result result = doc.load_file("tree.xml");

	/*
		The way grabbing child nodes work is that you query the doc object which is the root node.
		Looking at the tree.xml, <Parent> is the child node of the doc object. You would simply call
		child(nameOfChildNode) to fetch the node that you input. 
		
		To get different attributes of the node, use the attribute(attributeName) to fetch the attribute. 
		
		However, this won't bring the value of the attribute, you must then call value() to fetch the actual content
		of the attribute.
	*/
	std::cout << "Load result: " << result.description() << " node name: " << doc.child("Parent").attribute("name").value() << std::endl;

	/*
		xml_node is an object that allows to store a node as a separate object, useful for not having to call
		doc.child().child().child().child()
	*/
	pugi::xml_node parent = doc.child("Parent");

	/*
		The xml_node object is mighty useful with for loops.
		In the first part of the loop, assign the xml_node using .child().
		2nd part, check to see if the current node is not null (using C++ iterators, pugi has a xml_node iterator class.
		3rd part, assign the node to the next node using next_sibling(nodeName)
			- This part depends on how the XML tree is structured
	*/
	for (pugi::xml_node child = parent.child("Child"); child; child = child.next_sibling("Child")) {
		std::cout << "Child contents: " << child.child_value() << std::endl;

		/*
			Note that if the attribute you check does not exist it does NOT mean that it is null, just empty.
			Therefore, if you want to check if it exists, call the attribute with .attribute() then call .empty();
		*/
		if (!child.attribute("attribute").empty()) {

			/*
				If you want to separate the attribute of a node to its
				own object, use the xml_attribute type.
			*/
			pugi::xml_attribute attr = child.attribute("attribute");
			std::cout << "Child Attribute: " << attr.value() << std::endl;
		}
	}

	/*
		Summary:
		- Have an object for the whole document using xml_document type object.
		- Load it into the program using load_file(path)
			- Optionally, load it into a xml_parse_result to check for errors.
		- Access elements using xml_node and xml_attribute
			- Utilize xml_node and next_sibling for a for loop.
		- Use empty() to make check if the attributes exists.
	*/
	return 0;
}

