#include<iostream>
#include<fstream>
#include<string>
using namespace std;
void help()
{
	cout<<"R:��ȡ�ı��ļ�����������"<<endl;
	cout<<"M:���¶����ļ�"<<endl;
	cout<<"W:���浱ǰ�ļ�"<<endl;
	cout<<"V:��ʾ��ǰ�ļ�����"<<endl; 
	cout<<"Y:�½���һ���ı��ļ�"<<endl;
	cout<<"I:�����µ�һ��"<<endl;
	cout<<"D:ɾ��һ��"<<endl;
	cout<<"F:����ĳ���Ӵ�"<<endl;
	cout<<"C:�滻ĳ���Ӵ�"<<endl;
	cout<<"J:�滻ĳһ��"<<endl; 
	cout<<"Q:�˳��༭��"<<endl;
	cout<<"H/h:��ʾ������������İ�����Ϣ"<<endl;
	cout<<"T:ͳ���ļ��������ַ���"<<endl; 
	cout<<"N:��ǰ���ƶ�����һ��"<<endl;
	cout<<"P:��ǰ���ƶ�����һ��"<<endl;
	cout<<"B:��ǰ���ƶ�����һ��"<<endl;
	cout<<"E:��ǰ���ƶ������һ��"<<endl;
	cout<<"G:��ǰ���ƶ���ָ����ĳһ��"<<endl;
}
struct Node
{
	char ch;
	Node *next;
};
struct Row
{
	Node* line;
	Row* next;
};
Node* createNode(char ch)
{
	Node *p = new Node;
	p->ch = ch;
	p->next = NULL;
	return p;
}
Row* createRow(Node* p)
{
	Row* p_row = new Row;
	p_row->line = p;
	p_row->next = NULL;
	return p_row;
}
Node* find_node(Node* p, int n)
{
	int count = -1;
	Node* pp = p;
	while(pp != NULL&&count < n)
	{
		pp = pp->next;
		count++;
	}
	return pp;
}
Row* find_row(Row* text, int n)
{
	Row* p = text;
	int count = -1;
	while(p != NULL&&count < n)
	{
		p = p->next;
		count++;
	}
	return p; 
}

void insert_node(Node* list, int n, char ch)
{
	Node* p = find_node(list, n - 1);
	if(p)
	{
		Node* node = createNode(ch);
		node->next = p->next;
		p->next = node;
		return;
	}
	return;
}

void clear_node(Node* p)
{
	Node* temp = p->next;
	Node* pp;
	while(temp != NULL)
	{
		pp = temp->next;
		delete temp;
		temp = pp;
	}
}
void remove_node(Node* p, int n)
{
	Node* pnew = find_node(p, n - 1);
	Node* temp = NULL;
	if((pnew != NULL)&&(pnew->next != NULL))
	{
		temp = pnew->next;
		pnew->next = temp->next;
		delete temp;
		return;
	}
}
void remove_row(Row* p, int n)
{
	Row* pnew = find_row(p, n - 1);
	Row* temp = NULL;
	if((pnew != NULL)&&(pnew->next != NULL))
	{
		temp = pnew->next;
		pnew->next = temp->next;
		clear_node(temp->line);
		delete temp->line;
		delete temp;
	}
} 

void clear_row(Row* text)
{
	Row* p = text->next;
	Row* temp;
	while(p)
	{
		temp = p->next;
		clear_node(p->line);
		delete p->line;
		delete p;
		p = temp;
	}
}


void printall(Row* text)
{
	Row *p_row = text->next;
	Node *p_node;
	int i = 0;
	while(p_row != NULL)
	{
		p_node = p_row->line->next;
		while(p_node != NULL)
		{
			cout<<p_node->ch;
			p_node = p_node->next;
		}
		cout<<endl;
		p_row = p_row->next;
	} 

}
void openfile(char* filename, Row* text)
{
	ifstream file(filename);
	if(!file)
	{
		cout<<"�ļ���ȡʧ�ܣ�"<<endl;
		return;
	}
	char c;
	Row* p_row;
	p_row = text;
	while(!file.eof())
	{
		Node* pnull = new Node;
		pnull->next = NULL;
		Node* p_node = pnull;
		file.get(c);
		while(c != '\n'&&!file.eof())
		{
			Node* temp = createNode(c);
			temp->next = NULL;
			p_node->next = temp;
			p_node = p_node->next;
			file.get(c);
		}
		if(!file.eof())
		{
			Row* temp = createRow(pnull);
			p_row->next = temp;
			p_row = p_row->next; 
		}
	}
	file.close();
}
void createfile(const char* filename, Row* text)
{
	ofstream file(filename);
	if(!file)
	{
		cout<<"�ļ�����ʧ�ܣ�"<<endl;
		return;
	}
	file.close();
}
void savefile(char* filename, Row* text)
{
	ofstream file(filename);
	if(!file)
	{
		cout<<"�ļ�����ʧ�ܣ�"<<endl;
		return;
	}
	Row* p_row = text->next;
	Node* p_node = NULL;
	while(p_row != NULL)
	{
		p_node = p_row->line->next;
		while(p_node != NULL)
		{
			file<<p_node->ch;
			p_node = p_node->next;
		}
		file<<endl;
		p_row = p_row->next;
	}	
	file.close();
}
void insertstring(Row* text, int row)
{
	Row *p_row, *temp_row;
	Node *p_node, *temp_node;
	int i = -1;
	p_row = text;
	while(p_row->next&&i <= row)
	{
		p_row = p_row->next;
		i++;
	}
	while(i <= row)
	{
		temp_node = createNode(' ');
		temp_row = createRow(temp_node);
		p_row->next = temp_row;
		p_row = p_row->next;
		i++;
	}
	p_node = p_row->line;
	string s;
	cin>>s;
	for(int k = 0; k < s.length();k++)
	{
		temp_node = createNode(s[k]);
		temp_node->next = p_node->next;
		p_node->next = temp_node;
		p_node = p_node->next;
	} 
	temp_node = createNode('\n');
	temp_node->next = p_node->next;
	p_node->next = temp_node;
	p_node = p_node->next; 
}
void insertstring2(Row* text, int row)
{
	Row *p_row, *temp_row;
	Node *p_node, *temp_node;
	int i = -1;
	p_row = text;
	while(p_row->next&&i <= row)
	{
		p_row = p_row->next;
		i++;
	}
	while(i <= row)
	{
		temp_node = createNode(' ');
		temp_row = createRow(temp_node);
		p_row->next = temp_row;
		p_row = p_row->next;
		i++;
	}
	p_node = p_row->line;
	string s;
	cin>>s;
	for(int k = 0; k < s.length();k++)
	{
		temp_node = createNode(s[k]);
		temp_node->next = p_node->next;
		p_node->next = temp_node;
		p_node = p_node->next;
	} 
}
void total(Row* text)
{
	Row* p1 = text->next;
	Node* p2;
	int r = 0, c = 0;
	while(p1 != NULL)
	{
		r++;
		p2 = p1->line->next;
		while(p2 != NULL)
		{
			c++;
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	cout<<"�ܹ�"<<r<<"��, "<<c<<"���ַ���"<<endl;
}
int totalrow(Row* text)
{
	Row* p = text->next;
	int count = 0;
	while(p != NULL)
	{
		count++;
		p = p->next;
	}
	return count;
}
int totalcol(Row* text, int row)
{
	Row* p1 = text->next;
	Node* p2;
	int r = 0, c = 0;
	while(p1 != NULL&&r < row)
	{
		p2 = p1->line->next;
		p1 = p1->next; 
		r++;
	}
	while(p2 != NULL)
	{
		p2 = p2->next;
		c++;
	}
	return c;
	
}
void moverow(Row* text, int row, int poz)
{
	if(row == poz)
	{
		return;
	}
	Row* p = find_row(text, row - 1);
	Row* p_new = find_row(text, poz - 1);
	Row* temp;
	if((p != NULL)&&(p->next != NULL)&&(p_new != NULL))
	{
		temp = p->next;
		p->next = temp->next;
		temp->next = p_new->next;
		p_new->next = temp;
	}
}
void findstring(Row* text)
{
	string s;
	int pos, k = 0, row = 1, col = 0;
	cout<<"������Ҫ���ҵ��ַ���:"<<endl;
	cin>>s;
	Row* p = text->next;
	while(p != NULL)
	{
		string ss;
		Node* temp = p->line->next;
		while(temp != NULL)
		{
			ss.append(1,temp->ch);
			temp = temp->next;
		}
		pos = ss.find(s.c_str(), 0);
		while(pos != string::npos)
		{
			col = pos;
			k++;
			cout<<s<<"��"<<k<<"�γ��ֵ�λ����:��"<<row<<"��,��"<<col + 1<<"��"<<endl; 
			pos = ss.find(s.c_str(), col + 1);
		}
		row++;
		p = p->next;
	}
}
void changestring(Row* text)
{
	string s, snew;
	int pos, k = 0, row = 1, col = 0;
	cout<<"������Ҫ�滻���ַ���:"<<endl;
	cin>>s;
	cout<<"������Ҫ�滻��Ϊ���ַ���"<<endl;
	Row* p = text->next;
	while(p)
	{
		string ss;
		Node* temp = p->line->next;
		while(temp != NULL)
		{
			ss.append(1,temp->ch);
			temp = temp->next;
		}
		pos = ss.find(s.c_str(), 0);
		while(pos != string::npos)
		{
			col = pos;
			k++;
			cin>>snew;
			int j;
			for(j = 0; j < s.length();j++)
			{
				remove_node(p->line, col);
			}
			for(j = 0; j < snew.length(); j++)
			{
				insert_node(p->line, col + j, snew[j]);
			}
			pos = ss.find(s.c_str(), col + s.length());			
		}
	row++;
	p = p->next;
		
	}
}
void deletestring(Row* text, int row, int len)
{
	Row* p_row = find_row(text, row);
	Node* p_node = find_node(p_row->line, -1);
	Node* temp = p_node->next;
	int count = 0;
	while((temp != NULL)&&count < len)
	{
		p_node->next= temp->next;
		delete temp;
		temp = p_node->next;
		count++;
	}
}
int main()
{
	int sel, row, col, poz;
	Row* text = new Row;
	char ch;
	text->next = NULL;
	char filename[20];
	cout<<"��ѡ�������";
	cin>> ch;
	while(ch != 'Q')
	{
		if(ch == 'R')
		{
			cout<<"������Ҫ�򿪵��ļ����ƣ�"<<endl;
			cin>>filename;
			openfile(filename, text);
		}
		else if(ch == 'M')
		{
			openfile(filename, text);
		} 
		else if(ch == 'W')
		{
			savefile(filename, text);	
		}
		else if(ch == 'Y')
		{
			clear_row(text);
			cout<<"������Ҫ�½������ļ����ƣ�"<<endl;
			cin>>filename;
			createfile(filename, text);
		}
		else if(ch == 'I')
		{
			string str;
			cout<<"������Ҫ�����ڵڼ��к�"<<endl;
			cin>>row;
			cout<<"������Ҫ������ַ�����"<<endl;
			row--;
			insertstring(text, row);
		}
		else if(ch == 'D')
		{
			int len;
			cout<<"������Ҫɾ�����ַ�������"<<endl;
			cin>>row;
			len = totalcol(text, row);
			row--; 
			deletestring(text, row, len);
		} 
		else if(ch == 'F')
		{
			findstring(text);
		}
		else if(ch == 'C')
		{
			changestring(text);
		}
		else if(ch == 'J')
		{
			cout<<"������Ҫ�滻������"<<endl;
			cin>>row;
			int len = totalcol(text, row);
			row--;
			deletestring(text, row, len);
			cout<<"������Ҫ�滻��Ϊ���ַ�����"<<endl;
			row--; 
			 insertstring2(text, row);
		}
		else if(ch == 'G')
		{
			cout<<"��ѡ��Ҫ�ƶ�����"<<endl;
			cin>>row;
			cout<<"Ҫ����"<<row<<"���ƶ����ڼ���֮ǰ��";
			cin>>poz;
			row--;
			poz--;
			moverow(text, row, poz);
		}
		else if(ch == 'N')
		{
			cout<<"��ѡ��Ҫ�ƶ�����"<<endl;
			cin>>row;
			poz = row - 1;
			row--;
			poz--;
			moverow(text, row, poz);
		}
		else if(ch == 'P')
		{
			cout<<"��ѡ��Ҫ�ƶ�����"<<endl;
			cin>>row;
			poz = row - 1;
			row--;
			poz--;
			moverow(text, row, poz);
		}
		else if(ch == 'B')
		{
			cout<<"��ѡ��Ҫ�ƶ�����"<<endl;
			cin>>row;
			poz = 1;
			row--;
			poz--;
			moverow(text, row, poz);
		}
		else if(ch == 'E')
		{
			cout<<"��ѡ��Ҫ�ƶ�����"<<endl;
			cin>>row;
			poz = totalrow(text) + 1;
			row--;
			poz--;
			moverow(text, row, poz);
		}
		else if(ch == 'V')
		{
			printall(text);
		}
		else if(ch == 'H'||ch == 'h')
		{
			help(); 
		}
		else if(ch == 'T')
		{
			total(text);	
		}		
		cout<<"��ѡ�������";
		cin>> ch;	
	}
	clear_row(text);
	delete text;
	return 0;
} 
