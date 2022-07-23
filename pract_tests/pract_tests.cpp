#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include "sum_pract/graph.h"

TEST(GraphTest, InitTest){
	graph g(5);
	ASSERT_EQ(5, g.used.size());
	ASSERT_EQ(5, g.g.size());
	ASSERT_EQ(5, g.g[0].size());
}

TEST(GraphTest, AddEdgeTest){
	graph g(10);
	g.add_edge(1, 2);
	g.add_edge(2, 7);
	g.add_edge(1, 9);
	ASSERT_EQ(g.g[0][1], 1);
	ASSERT_EQ(g.g[1][6], 1);
	ASSERT_EQ(g.g[0][8], 1);

	ASSERT_EQ(g.g[1][0], 1);
	ASSERT_EQ(g.g[6][1], 1);
	ASSERT_EQ(g.g[8][0], 1);

	ASSERT_EQ(g.g[9][1], 0);
}

TEST(GraphTest, RmEdgeTest){
	graph g(4);
	g.add_edge(1, 2);
	g.add_edge(6);
	g.add_edge(3, 4);
	g.rm_edge(1);
	g.rm_edge(11);


	ASSERT_EQ(g.g[0][1], 2);
	ASSERT_EQ(g.g[1][2], 1);
	ASSERT_EQ(g.g[2][3], 2);

	ASSERT_EQ(g.g[1][0], 2);
	ASSERT_EQ(g.g[2][1], 1);
	ASSERT_EQ(g.g[3][2], 2);

	ASSERT_EQ(g.g[1][1], 0);
}

TEST(GraphTest, DepthFirstSearchTest){
	graph g(6);
	g.add_edge(1, 2);
	g.add_edge(3, 4);
	g.add_edge(3, 5);
	g.add_edge(5, 6);


	g.dfs(4);

	std::vector<bool>check1 = {0, 0, 1, 1, 1, 1};
	ASSERT_EQ(check1, g.used);

	std::fill(g.used.begin(), g.used.end(), 0);
	g.dfs(1);

	std::vector<bool>check2 = {1, 1, 0, 0, 0, 0};
	ASSERT_EQ(check2, g.used);
}

TEST(GraphTest, DestinitionTest){
	graph g(6);
	g.add_edge(1, 2);
	g.add_edge(3, 4);
	g.add_edge(3, 5);
	g.add_edge(5, 6);


	ASSERT_EQ(g.dest(1, 2), 1);
	ASSERT_EQ(g.dest(2, 4), 0);
	ASSERT_EQ(g.dest(4, 2), 0);
	ASSERT_EQ(g.dest(4, 6), 1);
	ASSERT_EQ(g.dest(6, 4), 1);
	ASSERT_EQ(g.dest(5, 4), 1);
}

TEST(GraphTest, DestinitionInEmptyGraphTest){
	graph g(6);

	

	ASSERT_EQ(g.dest(1, 2), 0);
	ASSERT_EQ(g.dest(2, 4), 0);
	ASSERT_EQ(g.dest(4, 2), 0);
	ASSERT_EQ(g.dest(4, 6), 0);
	ASSERT_EQ(g.dest(6, 4), 0);
	ASSERT_EQ(g.dest(5, 4), 0);
}

TEST(GraphTest, DestinitionInFullGraphTest){
	graph g(4);

	g.add_edge(1, 2);
	g.add_edge(1, 3);
	g.add_edge(1, 4);
	g.add_edge(2, 3);
	g.add_edge(2, 4);
	g.add_edge(3, 4);

	ASSERT_EQ(g.dest(1, 2), 1);
	ASSERT_EQ(g.dest(1, 3), 1);
	ASSERT_EQ(g.dest(1, 4), 1);
	ASSERT_EQ(g.dest(2, 3), 1);
	ASSERT_EQ(g.dest(2, 4), 1);
	ASSERT_EQ(g.dest(3, 4), 1);
}


TEST(MainTest, Test1) {

	std::ofstream fout;
	fout.open("output.txt");
	long long n = 10;
	graph g(n);
	g.add_edge(1, 2);
	g.add_edge(2, 3);
	g.add_edge(3, 5);
	g.add_edge(5, 1);
	g.add_edge(1, 4);
	g.add_edge(2, 4);
	g.add_edge(3, 4);
	g.add_edge(5, 4);
	g.add_edge(5, 6);
	g.add_edge(6, 7);
	g.add_edge(6, 9);
	g.add_edge(6, 10);
	g.add_edge(7, 8);
	g.add_edge(7, 9);
	g.add_edge(8, 9);
	g.add_edge(8, 10);
	g.add_edge(9, 10);
	std::vector<std::vector<long long>>g_first = g.g;
	
	std::string q = task(g, 1, 10);  
	g.print(fout, "Test1");
	fout.close();
	system("python3 ~/Desktop/sum/pract_src/sum_pract/draw.py");


	long long err = 0;
	long long delc = 0;

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(g_first[i][j] == 0 && g_first[i][j] != g.g[i][j])
				err++;
			if(g.g[i][j] == 2)
				delc++;
		}

	}
	ASSERT_EQ(q, "Sol");
	ASSERT_EQ(delc, 6);
	ASSERT_EQ(err, 0);
	ASSERT_EQ(g.dest(1, 10), 0);
	
}

TEST(MainTest, Test2) {

	std::ofstream fout;
	fout.open("output.txt");
	long long n = 5;
	graph g(n);
	g.add_edge(1, 2);
	g.add_edge(1, 3);
	g.add_edge(1, 4);
	g.add_edge(1, 5);
	g.add_edge(2, 3);
	g.add_edge(2, 4);
	g.add_edge(2, 5);
	g.add_edge(3, 4);
	g.add_edge(3, 5);
	g.add_edge(4, 5);
	
	std::string q = task(g, 1, 5);  
	g.print(fout, "Test2");
	fout.close();
	system("python3 ~/Desktop/sum/pract_src/sum_pract/draw.py");

	ASSERT_EQ(q, "NoSol");

	
}

TEST(MainTest, Test3) {

	std::ofstream fout;
	fout.open("output.txt");
	long long n = 10;
	graph g(n);
	g.add_edge(1, 2);
	g.add_edge(1, 3);
	g.add_edge(1, 4);
	g.add_edge(1, 5);
	g.add_edge(2, 3);
	g.add_edge(2, 4);
	g.add_edge(2, 5);
	g.add_edge(3, 4);
	g.add_edge(3, 5);
	g.add_edge(4, 5);
	g.add_edge(6, 7);
	g.add_edge(6, 8);
	g.add_edge(6, 9);
	g.add_edge(6, 10);
	g.add_edge(7, 8);
	g.add_edge(7, 9);
	g.add_edge(7, 10);
	g.add_edge(8, 9);
	g.add_edge(8, 10);
	g.add_edge(9, 10);

	g.add_edge(2, 10);
	g.add_edge(3, 9);
	g.add_edge(4, 8);
	std::vector<std::vector<long long>>g_first = g.g;
	
	std::string q = task(g, 1, 10);  
	g.print(fout, "Test3");
	fout.close();
	system("python3 ~/Desktop/sum/pract_src/sum_pract/draw.py");


	long long err = 0;
	long long delc = 0;

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(g_first[i][j] == 0 && g_first[i][j] != g.g[i][j])
				err++;
			if(g.g[i][j] == 2)
				delc++;
		}

	}
	ASSERT_EQ(q, "Sol");
	ASSERT_EQ(delc, 6);
	ASSERT_EQ(err, 0);
	ASSERT_EQ(g.dest(1, 10), 0);
	
}

TEST(MainTest, Test4) {

	std::ofstream fout;
	fout.open("output.txt");
	long long n = 10;
	graph g(n);
	g.add_edge(1, 2);
	g.add_edge(1, 3);
	g.add_edge(1, 4);
	g.add_edge(1, 5);
	g.add_edge(2, 3);
	g.add_edge(2, 4);
	g.add_edge(2, 5);
	g.add_edge(3, 4);
	g.add_edge(3, 5);
	g.add_edge(4, 5);
	g.add_edge(6, 7);
	g.add_edge(6, 8);
	g.add_edge(6, 9);
	g.add_edge(6, 10);
	g.add_edge(7, 8);
	g.add_edge(7, 9);
	g.add_edge(7, 10);
	g.add_edge(8, 9);
	g.add_edge(8, 10);
	g.add_edge(9, 10);

	g.add_edge(2, 10);
	g.add_edge(3, 9);
	g.add_edge(4, 8);
	g.add_edge(1, 6);
	std::vector<std::vector<long long>>g_first = g.g;
	
	std::string q = task(g, 1, 10);  
	g.print(fout, "Test4");
	fout.close();
	system("python3 ~/Desktop/sum/pract_src/sum_pract/draw.py");

	ASSERT_EQ(q, "NoSol");
	
}

TEST(MainTest, Test5) {

	std::ofstream fout;
	fout.open("output.txt");
	long long n = 10;
	graph g(n);
	g.add_edge(1, 2);
	g.add_edge(1, 3);
	g.add_edge(1, 4);
	g.add_edge(1, 5);
	g.add_edge(2, 3);
	g.add_edge(2, 4);
	g.add_edge(2, 5);
	g.add_edge(3, 4);
	g.add_edge(3, 5);
	g.add_edge(4, 5);
	g.add_edge(6, 7);
	g.add_edge(6, 8);
	g.add_edge(6, 9);
	g.add_edge(6, 10);
	g.add_edge(7, 8);
	g.add_edge(7, 9);
	g.add_edge(7, 10);
	g.add_edge(8, 9);
	g.add_edge(8, 10);
	g.add_edge(9, 10);

	g.add_edge(2, 10);
	std::vector<std::vector<long long>>g_first = g.g;
	
	std::string q = task(g, 1, 10);  
	g.print(fout, "Test5");
	fout.close();
	system("python3 ~/Desktop/sum/pract_src/sum_pract/draw.py");


	long long err = 0;
	long long delc = 0;

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(g_first[i][j] == 0 && g_first[i][j] != g.g[i][j])
				err++;
			if(g.g[i][j] == 2)
				delc++;
		}

	}
	ASSERT_EQ(q, "Sol");
	ASSERT_EQ(delc, 6);
	ASSERT_EQ(err, 0);
	ASSERT_EQ(g.dest(1, 10), 0);
	
}

