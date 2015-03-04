/*
Copyright (c) 2012-2015 The SSDB Authors. All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "node.h"
#include "cluster.h"

int main(int argc, char **argv){
	Cluster cluster;
	cluster.init();
	
	printf("init node_list:\n");
	cluster.print_node_list();
	
	Node *node1, *node2;
	
	if(0){
		printf("press Enter to init nodes: ");
		getchar();

		node1 = cluster.connect_node("127.0.0.1", 8888);
		node2 = cluster.connect_node("127.0.0.1", 8889);
		if(!node1 || !node2){
			printf("init node error!\n");
			return 0;
		}
	
		cluster.add_kv_node(node1);
		printf("node_list:\n");
		cluster.print_node_list();

		cluster.split_kv_node(node1, node2);
		printf("node_list:\n");
		cluster.print_node_list();
	}else{
		node1 = cluster.get_node(1);
		node2 = cluster.get_node(2);
		if(!node1 || !node2){
			printf("init node error!\n");
			return 0;
		}
	}
	
	while(1){
		printf("Press Enter to migrate_kv_data: ");
		getchar();
		cluster.migrate_kv_data(node1, node2);
		printf("node_list:\n");
		cluster.print_node_list();
	}

	delete node1;
	delete node2;
	
	return 0;
}
