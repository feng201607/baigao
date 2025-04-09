#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

vector<vector<unordered_set<int>>> lastRemainingCellInference (vector<vector<int>>& cells) //确定某个区域（行、列、九宫格）只有某格可以填入某数字
{
    vector<vector<unordered_set<int>>> ans(9,vector<unordered_set<int>>(9,unordered_set<int>{1,2,3,4,5,6,7,8,9}));
	for(int i=0;i<9;i++)//初始化
	{
		for(int j=0;j<9;j++)
		{
			if(cells[i][j]!=0)
				ans[i][j].clear(); //如果该格已经填入数字，则该格的集合清空
		}
	}
	int change_flag=1;//标记答案数组是否发生更改
	while(change_flag)
	{
		change_flag=0;
		for(int i=0;i<9;i++)
		{
			for(int j=0;j<9;j++)
			{
				for(int k=0;k<9;k++)//从[i][j]中删除行有的数字
				{
					if(k!=j&&cells[i][k]!=0)
					{
						if(ans[i][j].erase(cells[i][k]))
						{
							change_flag=1;
						}
					}
				}
				for(int k=0;k<9;k++)//从[i][j]中删除列有的数字
				{
					if(k!=i&&cells[k][j]!=0)
					{
						if(ans[i][j].erase(cells[k][j]))
						{
							change_flag=1;
						}
					}
				}
				for(int k=0;k<9;k++)//从[i][j]中删除九宫格有的数字
				{
					int x=i/3*3+k/3;
					int y=j/3*3+k%3;
					if((x!=i||y!=j)&&cells[x][y]!=0)
					{
						if(ans[i][j].erase(cells[x][y]))
						{
							change_flag=1;
						}
					}
				}
				
				//若该行只有该单元格能填该数字，则确认该数字位置
				for(int k=1;k<=9;k++)
				{
					int count=0;
					for(int m=0;m<9;m++)
					{
						if(m!=j&&ans[i][m].find(k)!=ans[i][m].end())
						{
							count++;
						}
					}
					if(count==0&&ans[i][j].find(k)!=ans[i][j].end())
					{
						cells[i][j]=k;
						ans[i][j].clear();
						change_flag=1;
						break;
					}
					//若该列只有该单元格能填该数字，则确认该数字位置
					count=0;
					for(int m=0;m<9;m++)
					{
						if(m!=i&&ans[m][j].find(k)!=ans[m][j].end())
						{
							count++;
						}
					}
					if(count==0&&ans[i][j].find(k)!=ans[i][j].end())
					{
						cells[i][j]=k;
						ans[i][j].clear();
						change_flag=1;
						break;
					}
					//若该九宫格只有该单元格能填该数字，则确认该数字位置
					count=0;
					for(int m=0;m<9;m++)
					{
						int x=i/3*3+m/3;
						int y=j/3*3+m%3;
						if((x!=i||y!=j)&&ans[x][y].find(k)!=ans[x][y].end())
						{
							count++;
						}
					}
					if(count==0&&ans[i][j].find(k)!=ans[i][j].end())
					{
						cells[i][j]=k;
						ans[i][j].clear();
						change_flag=1;
						break;
					}
				}
			}
		}
	}
	return ans;
}

vector<vector<unordered_set<int>>> possibleNumberInference (vector<vector<int>>& cells) //确定某个单元格只能填那个数字
{
	vector<vector<unordered_set<int>>> ans(9,vector<unordered_set<int>>(9,unordered_set<int>{1,2,3,4,5,6,7,8,9}));
	for(int i=0;i<9;i++)//初始化
	{
		for(int j=0;j<9;j++)
		{
			if(cells[i][j]!=0)
				ans[i][j].clear(); //如果该格已经填入数字，则该格的集合清空
		}
	}
	int change_flag=1;//标记答案数组是否发生更改
	while(change_flag)
	{
		change_flag=0;
		for(int i=0;i<9;i++)
		{
			for(int j=0;j<9;j++)
			{
				for(int k=0;k<9;k++)//从[i][j]中删除行有的数字
				{
					if(k!=j&&cells[i][k]!=0)
					{
						if(ans[i][j].erase(cells[i][k]))
						{
							change_flag=1;
						}
					}
				}
				for(int k=0;k<9;k++)//从[i][j]中删除列有的数字
				{
					if(k!=i&&cells[k][j]!=0)
					{
						if(ans[i][j].erase(cells[k][j]))
						{
							change_flag=1;
						}
					}
				}
				for(int k=0;k<9;k++)//从[i][j]中删除九宫格有的数字
				{
					int x=i/3*3+k/3;
					int y=j/3*3+k%3;
					if(x!=i&&y!=j&&cells[x][y]!=0)
					{
						if(ans[i][j].erase(cells[x][y]))
						{
							change_flag=1;
						}
					}
				}
			}
		}
		//寻找有没有单元格只有一个数字可以填入
		for(int i=0;i<9;i++)
		{
			for(int j=0;j<9;j++)
			{
				if(cells[i][j]==0&&ans[i][j].size()==1)
				{
					cells[i][j]=*ans[i][j].begin();//填入该数字
					ans[i][j].clear();//清空该单元格的集合
					change_flag=1;
				}
			}
		}
	}
	return ans;
}

int main()//设计测试样例
{
	vector<vector<int>> cells1(9,vector<int>(9,0));
	cells1={{2,0,0,0,7,0,0,3,8},{0,0,0,0,0,6,0,7,0},{3,0,0,0,4,0,6,0,0},
			{0,0,8,0,2,0,7,0,0},{1,0,0,0,0,0,0,0,6},{0,0,7,0,3,0,4,0,0},
			{0,0,4,0,8,0,0,0,9},{0,6,0,4,0,0,0,0,0},{9,1,0,0,6,0,0,0,2}};
	vector<vector<int>> cells2(9,vector<int>(9,0));
	cells2={{0,7,0,0,0,8,0,2,9},{0,0,2,0,0,0,0,0,4},{8,5,4,0,2,0,0,0,0},
			{0,0,8,3,7,4,2,0,0},{0,0,0,0,0,0,0,0,0},{0,0,3,2,6,1,7,0,0},
			{0,0,0,0,9,0,6,1,2},{2,0,0,0,0,0,4,0,0},{1,3,0,6,0,0,0,7,0}};
	vector<vector<unordered_set<int>>> ans1=lastRemainingCellInference(cells1);
	vector<vector<unordered_set<int>>> ans2=lastRemainingCellInference(cells2);
	vector<vector<unordered_set<int>>> ans3=possibleNumberInference(cells1);
	vector<vector<unordered_set<int>>> ans4=possibleNumberInference(cells2);
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(cells1[i][j]==0)
			{
				cout<<"{";
				for (auto item : ans1[i][j])
				{
					cout<<item<<" ";
				}
				cout<<"} ";
			}
			else
			{
				cout<<cells1[i][j]<<" ";
			}
		}
		cout<<endl;
	}
}