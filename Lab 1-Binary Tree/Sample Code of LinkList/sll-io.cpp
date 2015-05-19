#include <iostream>
#include <fstream>

#define DEBUG	1
#define dout	if (DEBUG) std::cout

class SLLNode {
public:
	SLLNode(std::string &id, std::string &name) {
		this->id = id;
		this->name = name;
		this->next = NULL;
	}
	std::string getName() {
		return name;
	}
	std::string getID() {
		return id;
	}
	bool isNameEqual(std::string &secondname) {
		return name == secondname;
	}
	bool isIDEqual(std::string secondid) {
		return id == secondid;
	}
	void pointTo(SLLNode *nextnode) {
		this->next = nextnode;
	}
	SLLNode *getNext() {
		return next;
	}
private:
	std::string name;
	std::string id;
	class SLLNode *next;

};

class SLL {
public:	// from this interface, main need not know about SLLNode.
	SLL() {
		head = NULL;
	}
	void insert(std::string id, std::string name);
	void remove(std::string id);	// delete is a keyword.
	bool search(std::string id, std::string &name);
	void print();
	void print(std::string id, std::string name);
	void error(std::string msg);
	unsigned read(std::string file);

private:
	class SLLNode *head;
	void remove(SLLNode *prev, SLLNode *ptr);
};

unsigned SLL::read(std::string file) {
	std::ifstream in;
	std::string line;
	std::string id, name;

	in.open(file.c_str());	// doesn't work with strings.
	in >> id >> name;
	while (!in.eof()) {
		dout << id << "=" << name << std::endl;
		insert(id, name);
		in >> id >> name;
	}
	in.close();
}
void SLL::error(std::string msg) {
	std::cout << "ERROR: " << msg << std::endl;
}
void SLL::insert(std::string id, std::string name) {
	std::string oldname;
	if (search(id, oldname)) {
		error(id + ", " + oldname + " is already present.");
		return;
	}
	SLLNode *newstud = new SLLNode(id, name);
	newstud->pointTo(head);
	head = newstud;
}
void SLL::remove(SLLNode *prev, SLLNode *ptr) {
	// assume: ptr is non-null.
	if (prev) {
		prev->pointTo(ptr->getNext());
	} else {
		head = ptr->getNext();
	}
	delete ptr;
}
void SLL::remove(std::string id) {
	for (SLLNode *ptr = head, *prev = NULL; ptr; prev = ptr, ptr = ptr->getNext()) {
		if (ptr->isIDEqual(id)) {
			dout << id << " " << ptr->getName() << " removed from the class.\n";
			remove(prev, ptr);
			return;		// assuming no duplicates.
		}
	}
	error(id + " not present in the class.");
}
bool SLL::search(std::string id, std::string &name) {
	for (SLLNode *ptr = head; ptr; ptr = ptr->getNext()) {
		if (ptr->isIDEqual(id)) {
			name = ptr->getName();
			return true;
		}
	}
	return false;
}
void SLL::print(std::string id, std::string name) {
	std::cout << "\t- " << id << ", " << name << std::endl;
}
void SLL::print() {
	for (SLLNode *ptr = head; ptr; ptr = ptr->getNext()) {
		print(ptr->getID(), ptr->getName());
	}
}
int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Invalid number of arguments.\nUsage: " << argv[0] << " <datafile>\n";
		return 1;
	}
	SLL cs6140;
	cs6140.read(argv[1]);

	std::string name;
	if (cs6140.search("CS14M007", name)) {
		std::cout << "CS14M007 " << name << " is registered for the course.\n";
	} else {
		std::cout << "CS14M007 is not registered for the course.\n";
	}
	cs6140.remove("CS14D015");
	if (DEBUG) cs6140.print();
	// deallocate: add destructor. Add print statements to know the flow.
	return 0;
}
