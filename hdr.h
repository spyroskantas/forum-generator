#include<iostream>
#include<string>
using namespace std;

struct Date{
	int day;
	int month;
};

int rand_num(); //random 0-9 for randomly picking array items

int rand_id(); //for unique ids
	
int get_random_id(); //returns a random existing id


class Post{
	
	private:
		int id;
		string title;
		string creator;
		string content;
		Date date;
		
	public:
		Post(int, const string&, const string&, const Date&, const string&);
		
		int get_id() const;
		
		string get_creator() const;
		
		void print() const;

		~Post();
};

//node for post list
struct p_node{
	const Post& post;
	p_node *next;
};

//node for thread tree
struct t_node{
	string creator;
	p_node *posts;
	t_node *left;
	t_node *right;
};


class Thread{
	
	private:
		string creator;
		string subject;
		Date date;
		
	public:
		Post *posts;
		int post_count;
		
		Thread(const string&, const string&, const Date&);
		
		string get_subject() const;
	
		void print() const;

		~Thread();
};


class Forum{
	
	private:
		Thread *threads;
		string title;
		int thread_count;
		
		//Part 2//////////////////////////////////////
		void BSTInsert_Post(p_node*&, const Post&);
		
		void BSTInsert_Creator(t_node*&, const Post&);
		
		t_node* BSTTree(const Thread&);

		void BSTDestroyPostList(p_node* node);

		void BSTDestroy(t_node* node);
		
		void print_InOrder(t_node*);

		void breakdown_posts(t_node*&, p_node*);
		
		void breakdown_tree(t_node*&, t_node*);

		void Merge_Trees(t_node*&, t_node*);
		//////////////////////////////////////////////

	public:
		Forum(string);
		
		void print_sorted();
		
		void print() const;
	
		void print_Thread(const string&) const;
		
		void print_Post(int) const;

		~Forum();
};

