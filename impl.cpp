#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include"hdr.h"
using namespace std;



static string creators[10]={"Bob","Mark","John","Chris","Helen","George","Spyros","Iris","Mary","Lia"};
static string titles[10]={"title_1","title_2","title_3","title_4","title_5","title_6","title_7","title_8","title_9","title_10"};
static string posts[10]={"Hello","Can I ask something?","Thats right!","This is helpful, thanks!", "Thank you!","I dont know..","I'm forwarding this post.","Good question!","Correct anwser!","Is this right?"};
static Date dates[10]={{10,3}, {6,1}, {29,2}, {22,10}, {12,3}, {3,5}, {6,8}, {11,2}, {10,12}, {9,9}};\
static int id[100];
static int id_count=0;


int rand_num(){ //random 0-9 for randomly picking array items
	int r;
	r = rand() % 9;
	if(r == 0) return 1;
	else return r;
}

int rand_id(){ //for unique ids
	int i,r;
	r = rand();
	for(;;){
		for(i=0; i<100; i++)
			if(r == id[i]){
				r = rand();
				break;
			}
		if(i == 100) break;
	}
		
	id[id_count++] = r;
	return r;
}

int get_random_id(){ //returns a random existing id
	int r;
	r = rand() % id_count;
	return id[r];
}


//POST CLASS FUNCTIONS
Post::Post(int d=rand_id(), const string& titl=titles[rand_num()], const string& creat=creators[rand_num()], const Date& dat=dates[rand_num()], const string& cont=posts[rand_num()])
:	id(d), title(titl), creator(creat), date(dat), content(cont){
	
	cout<<"\t\tPost created! Creator: "<<creator<<"  Title: "<<title<<"  Date: "<<date.day<<"/"<<date.month<<"  id: "<<id<<"  Content: "<<content<<endl;
}

int Post::get_id() const{
	return id;
}

string Post::get_creator() const{
	return creator;
}

void Post::print() const{
	cout<<"\t\tCreator: "<<creator<<"  Title: "<<title<<"  Date: "<<date.day<<"/"<<date.month<<"  Content: "<<content<<endl;
}

Post::~Post(){
	cout<<"Post Number: "<<id<<" is about to get destroyed\n";
}


//THREAD CLASS FUNCTIONS
Thread::Thread(const string& subj=titles[rand_num()], const string& creat=creators[rand_num()], const Date& dat=dates[rand_num()])
: subject(subj), creator(creat), date(dat){
	
	cout<<"\n\tThread with subject: '"<<subject<<"' has just been created!\n\n";
	post_count = rand_num();
	posts = new Post[post_count];
}

string Thread::get_subject() const{
	return subject;
}
		
void Thread::print() const{
	cout<<"\nThread: "<<subject<<"   Creator: "<<creator<<"   Date: "<<date.day<<"/"<<date.month<<"  Posts:"<<endl;
	for(int i=0; i<post_count; i++)
		posts[i].print();
}

Thread::~Thread(){
	cout<<"\nThread with subject: "<<subject<<" is about to get destroyed\n\n";
	delete[] posts;
}


//FORUM CLASS FUNCTIONS
Forum::Forum(string titl)
: title(titl){
	cout<<"\nForum with title: '"<<title<<"' has just been created"<<endl;
	thread_count = rand_num();
	threads = new Thread[thread_count]{Thread("Rules and Tips")};
}

void Forum::BSTInsert_Post(p_node*& node, const Post& post){
	
	if(node == NULL){
		node = new p_node{post};
		node->next = NULL;
	}else
		BSTInsert_Post(node->next, post);
}

void Forum::BSTInsert_Creator(t_node*& node, const Post& post){
	
	if(node == NULL){
		
		node = new t_node{post.get_creator(), NULL, NULL, NULL};
		BSTInsert_Post(node->posts, post);
		
	}else if(post.get_creator() < node->creator) BSTInsert_Creator(node->left, post);
	else if(post.get_creator() > node->creator) BSTInsert_Creator(node->right, post);
	else BSTInsert_Post(node->posts, post);
}

t_node* Forum::BSTTree(const Thread& thread){
	
	t_node* root=NULL;
	
	for(int i=0; i<thread.post_count; i++){
		BSTInsert_Creator(root, thread.posts[i]);
	}
	return root;
}

void Forum::BSTDestroyPostList(p_node* node){

	if(node != NULL){
		BSTDestroyPostList(node->next);
		delete node;
	}
}

void Forum::BSTDestroy(t_node* node){

	if(node != NULL){
		BSTDestroy(node->left);
		BSTDestroy(node->right);
		BSTDestroyPostList(node->posts);
		delete node;
	}
}

void Forum::print_InOrder(t_node* node){
	
	if(node !=NULL){
		
		print_InOrder(node->left);
		
		cout<<node->creator<<endl;
		for(p_node *l=node->posts; l!=NULL; l=l->next)
			l->post.print();
			
		print_InOrder(node->right);
	}
}

void Forum::breakdown_posts(t_node*& a, p_node* node){
	
	if(node != NULL){
		breakdown_posts(a, node->next);
		BSTInsert_Creator(a, node->post);
		delete node;
	}
}


void Forum::breakdown_tree(t_node*& a, t_node* node){

	if(node != NULL){
		breakdown_tree(a, node->left);
		breakdown_tree(a, node->right);
		breakdown_posts(a, node->posts);
		delete node;
	}
}

void Forum::Merge_Trees(t_node*& a, t_node* b){

	breakdown_tree(a, b);
}

void Forum::print_sorted(){

	t_node *Tree=NULL;

	cout<<"\n\nPrinting  all Posts sorted by Names\n";
	for(int i=0; i<thread_count; i++)
		Merge_Trees(Tree, BSTTree(threads[i]));
	
	print_InOrder(Tree);
	BSTDestroy(Tree);
}

void Forum::print() const{
	cout<<"\n\nForum '"<<title<<"' has the following Threads:"<<endl;
	for(int i=0; i<thread_count; i++)
		cout<<"\t"<<threads[i].get_subject()<<endl;
}

void Forum::print_Thread(const string& subj) const{
	
	for(int i=0; i<thread_count; i++)
	
		if(threads[i].get_subject() == subj){
			
			threads[i].print();
			return;
		}
	cout<<"Thread not found"<<endl;
}

void Forum::print_Post(int id) const{
	
	for(int i=0; i<thread_count; i++)
		for(int k=0; k<threads[i].post_count; k++)
		
			if(threads[i].posts[k].get_id() == id){
				
				cout<<"\nPost with id: "<<id<<endl;
				threads[i].posts[k].print();
				return;
			}
	cout<<"Post not found"<<endl;
}

Forum::~Forum(){
	cout<<"\n\nForum: "<<title<<" is about to get destroyed\n";
	delete[] threads;
}
