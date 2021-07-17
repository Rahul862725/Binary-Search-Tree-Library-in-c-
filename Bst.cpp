#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#define null 0
using namespace std;
// Class for creating nodes of BST
template <typename T>
class Node{
public:
  T data;
  Node*left;
  Node*right;
  Node(){
    left=null;
    right=null;
  }
  Node(T val){
    data=val;
    left=null,right=null;
  }
};

//BST class
template <typename U>
class BST{
   Node<U>*head=null;
    // FUnction help in insertion element in BST
  Node<U>*traverse(Node<U>*head,U data){
     if(head==null){
       Node<U>*nw=new Node<U>(data);
       return nw;
     }
     if(head->data>data)
    head->left= traverse(head->left,data);
     else
     head->right=traverse(head->right,data);
     return head;
  }

  //Function help for some type traversal of BST like preorder,inorder,postorder
  void specificTraversal(Node<U>*head,vector<U>&va,int c)
  {
    if(head==null)
    return;
    if(c==0)
    {va.push_back(head->data);
      specificTraversal(head->left,va,c);
      specificTraversal(head->right,va,c);
    }
    else if(c==1)
    {
      specificTraversal(head->left,va,c);
      va.push_back(head->data);
      specificTraversal(head->right,va,c);
    }
    else if(c==2)
    {
      specificTraversal(head->left,va,c);
      specificTraversal(head->right,va,c);
      va.push_back(head->data);
    }
  }

  //Function conditionalDelete (conDelete) help in deleting any value from BST
  Node<U>*conDelete(Node<U>*head)
  {
    if(head->left==null&&head->right==null)
    return null;
    else if(head->left==null||head->right==null)
    {
      return head->left==null?head->right:head->left;
    }
    else
    {
      Node<U>*pr=head;
      Node<U>*tr=head;
      tr=tr->left;
      while(tr->right!=null)
      {pr=tr;
        tr=tr->right;
      }
      U t=head->data;
      head->data=tr->data;
      tr->data=t;
      if(head->left==tr)
      {
        pr->left=tr->left;
      }
      else
      pr->right=tr->left;
      return head;
    }
  }

  //Function help in searching and deleting
  Node<U>*Search(Node<U>*h,U data,int&itr)
  {
    if(h==null)
    return null;
    if(h->data==data)
    {
      if(itr!=0)
      itr=1;
      else
      {itr=1;
        Node<U>*findn=conDelete(h);
        return findn;
      }
    }
    else if(h->data>data)
    {
     h->left=  Search(h->left,data,itr);
    }
    else
  h->right= Search(h->right,data,itr);
  return h;
  }
  //User Accesible function
  public:
    BST(){}
    BST(U n,U arr[]){
      for(U i=0;i<n;i++)
      {
        insert(arr[i]);
      }
    }

//Copy Constructer
BST(BST<U>&obj1)
{
  Node<U>*tr=obj1.BSTHead();
  queue<Node<U>*>q;
  q.push(tr);
  while(!q.empty())
  {
    Node<U>*findn=q.front();
    head=insert(head,findn->data);
    q.pop();
    if(findn->left!=null)
    q.push(findn->left);
    else if(findn->right!=null)
    q.push(findn->right);
  }
}
 //Return the Head of BST
  Node<U>*BSTHead(){
    return head;
  }

  //Insert a element
  void insert(U data){
    head=traverse(head,data);
  }

//delete a element
  bool Delete(U data)
  {int itr=0;
  head=Search(head,data,itr);
  if(itr==0)
  return false;
  else
  return true;
  }

//Search a element
  bool search(U data)
   {int itr=-1;
    Search(head,data,itr);
    if(itr==-1) return false;
    else return true;
   }

   //Preorder traversal
  vector<U> preOrder(){
     vector<U>va;
     specificTraversal(head,va,0);
     return va;
  }

//inorder traversal
  vector<U> inOrder(){
     vector<U>va;
     // specificTraversal(head,va,1);
     // return va;
     stack<Node<U>*>st;
     st.push(head);
     Node<U>*tr=head;
     Node<U>*pr=null;
     while(!st.empty())
     {
       if(tr!=null)
       {if(tr->left!=null)
         st.push(tr->left);
         pr=tr;
         tr=tr->left;
       }
       else
       {
         tr=st.top();
          va.push_back(tr->data);
         tr=tr->right;

       }
     }
       return va;
  }

//postorder traversal
  vector<U> postOrder(){
     vector<U>va;
     specificTraversal(head,va,2);
     return va;
  }

//levelorder traversal
  vector<U>levelOrder()
  {
    vector<U>va;
    queue<Node<U>*>q;
    Node<U>*tr=head;
    q.push(tr);
    while(!q.empty())
    { tr=q.front();
      va.push_back(tr->data);
      q.pop();
      if(tr->left!=null)
      q.push(tr->left);
      if(tr->right!=null)
      q.push(tr->right);
    }
    return va;
  }

  U Successor(U data)
  {
    stack<Node<U>*>st;
    st.push(head);
    Node<U>*tr=head;
    Node<U>*pr=null;
    while(!st.empty())
    {
      if(tr!=null)
      {if(tr->right!=null)
        st.push(tr->right);
        pr=tr;
        tr=tr->right;
      }
      else
      {
        tr=st.top();
        if(tr->data==data)
        return pr->data;
        tr=tr->left;

      }
    }
    return -1;
  }

  U Predessor(U data)
  {
    stack<Node<U>*>st;
    st.push(head);
    Node<U>*tr=head;
    Node<U>*pr=null;
    while(!st.empty())
    {
      if(tr!=null)
      {if(tr->left!=null)
        st.push(tr->left);
        pr=tr;
        tr=tr->left;
      }
      else
      {
        tr=st.top();
        if(tr->data==data)
        return pr->data;
        tr=tr->right;

      }
    }
    return -1;
  }
};
int main()
{

  int n;
  cin>>n;
  int ar[n];
  for(int i=0;i<n;i++)
  {
    cin>>ar[i];
  }
   BST<int>a(n,ar);
   vector<int>va=a.inOrder();
   a.Delete(va[0]);
   va=a.inOrder();
   for(int i=0;i<va.size();i++)
   {
     cout<<va[i]<<" ";
   }
  // cout<<a.BSTHead()->right->data;
}
