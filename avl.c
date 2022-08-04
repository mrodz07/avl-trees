/*
 * AVL Trees
*/

#include <stdlib.h> 
#include <string.h>
#include <stdio.h> 
#include <math.h> 

static const int MAX_SIZE = 1024; 

typedef struct Node { 
    int is_available;  
    char * id; 
    char * str1; 
    char * str2; 
    struct Node * rgt; 
    struct Node * lft; 
	struct Node * prv; 
} Node; 

typedef struct ListNode { 
    struct ListNode * nxt; 
    Node * dat; 
} ListNode; 

ListNode * mk_list_node(Node * dat) { 
    ListNode * tmp = malloc(sizeof(ListNode));
    tmp -> dat = dat; 
    tmp -> nxt = NULL; 
    return tmp; 
}

Node * mk_node(char * id, char * str1, char * str2) { 
    Node * tmp = malloc(sizeof(Node));
    tmp -> id = id; 
    tmp -> str1 = str1; 
    tmp -> str2 = str2; 
    tmp -> rgt = NULL; 
    tmp -> lft = NULL; 
    tmp -> is_available = 1; 
    return tmp; 
}

Node * srch_id(Node ** root, char * tmp_id) { 
    Node * tmp = malloc(sizeof(Node)); 
    tmp = (* root); 
    while(tmp != NULL) { 
        if(strcmp(tmp -> id, tmp_id) == 0) 
            return tmp; 
        else if(strcmp(tmp -> id, tmp_id) > 0)
            tmp = tmp -> lft; 
        else if(strcmp(tmp -> id, tmp_id) < 0)
            tmp = tmp -> rgt; 
    }
    return NULL; 
}

void pnt_node(Node * node) { 
    printf("\nid: %sstr1: %sstr2: %s\n", node -> id, node -> str1, node -> str2); 
}

void queue(ListNode ** head, ListNode * lnode) { 
	ListNode * tmp = (* head); 
	if(tmp) { 
		while((tmp) -> nxt) { 
			tmp = tmp -> nxt; 		
		}	
	tmp -> nxt = lnode; 
	}
	else { 
		(* head) = lnode; 
	}
}

void dfs_lst(ListNode ** head, Node * node) { 
    if( (node -> lft) != NULL)  
        dfs_lst(head, node -> lft); 
    if( (node -> rgt) != NULL) 
        dfs_lst(head, node -> rgt); 
    queue(head, mk_list_node(node)); 
}

void cln_list_node(ListNode * tmp) { 
	tmp -> nxt = NULL;
	tmp -> dat = NULL; 
}

ListNode * dequeue(ListNode ** head) { 
	ListNode * tmpn = NULL; 
	ListNode * tmp = (* head); 
	if(tmp) { 
		if(tmp -> nxt) { 
		ListNode * tmp_nxt = tmp -> nxt; 
		(* head) = tmp_nxt; 	
	}
	else
		(* head) = NULL; 
	tmpn = tmp; 
    }
    else
        (* head) = NULL; 
    return tmpn;
}

ListNode * pop(ListNode ** head) { 
    ListNode * tmpn = NULL; 
    ListNode * prv = NULL; 
    ListNode * tmp = NULL; 
    if( (* head) != NULL) { 
        tmp = (* head); 
        if( (tmp -> nxt) == NULL) { 
            (* head) = NULL; 
        }
        else { 
            while(tmp -> nxt) { 
                prv = tmp; 
                tmp = tmp -> nxt;
            }
            prv -> nxt = NULL; 
        }
        tmpn = tmp; 
        cln_list_node(tmp); 
        free(tmp); 
    }
    return tmpn;
}

void push(ListNode ** head, ListNode * node) { 
    ListNode * tmp = (* head); 
    if(tmp) { 
        while((tmp) -> nxt) { 
            tmp = tmp -> nxt; 
        }
    tmp -> nxt = node; 
    }
    else { 
        (* head) = node; 
    }
}

ListNode * get_list_element(ListNode ** head, int n) { 
	ListNode * tmp = NULL; 
	int i = 0; 
	if( (* head) && (n>=0) ) { 
		tmp = (* head); 
		while(i<n) { 
			tmp = tmp -> nxt; 
			i++; 
		}
	}
	return tmp; 
}

int cnt_lst(ListNode ** head) { 
	ListNode * tmp = (* head); 
	int cnt = 0; 
	while(tmp) { 
		cnt++; 
		tmp = tmp -> nxt; 	
	}
	return cnt; 
}

int max_num(int n1, int n2) { 
	if(n1>n2)
		return n1; 
	return n2; 
}

int height(Node * node) {
	if(node == NULL) 
		return 0; 
	else return 1 + max_num(height(node -> rgt), height(node -> lft)); 
} 

void swap(ListNode ** head, int i, int j) { 
    ListNode * lft_node = get_list_element(head, i); 
	ListNode * rgt_node = get_list_element(head, j); 
	ListNode * tmp = rgt_node -> nxt; 
	if( (* head) == lft_node) { 
		(* head) = rgt_node; 
    }
	rgt_node -> nxt = lft_node; 
	lft_node -> nxt = tmp; 
	if(get_list_element(head, i-1) != NULL) { 
		ListNode * lft_mst_node = get_list_element(head, i-1); 
		lft_mst_node -> nxt = rgt_node; 
	}
}

void pnt_lst(ListNode * list_node) { 
    if(list_node != NULL) { 
        printf("id: %sstr1: %sstr2: %s", list_node -> dat -> id, list_node -> dat -> str1, list_node -> dat -> str2); 
        printf("\n");
        pnt_lst(list_node -> nxt); 
    }
}

void asort_id(ListNode ** head) { 
	int num = cnt_lst(head); 
	for(num; num>=2; num--) {
		for(int i=0; i<num-1; i++) {
			if(strcmp(get_list_element(head, i) -> dat -> id, get_list_element(head, i+1) -> dat -> id) > 0) { 
				swap(head, i, i+1); 
			}
		}
	}
}

void dsort_id(ListNode ** head) { 
    int num = 0;
	num = cnt_lst(head); 
	for(num; num>=2; num--){
		for(int i=0; i<num-1; i++) {
			if(strcmp(get_list_element(head, i) -> dat -> id, get_list_element(head, i+1) -> dat -> id) < 0) { 
				swap(head, i, i+1); 
			}
		}
	}
}

void asort_str1(ListNode ** head) { 
    int num = 0;
	num = cnt_lst(head); 
	for(num; num>=2; num--){
		for(int i=0; i<num-1; i++) {
			if(strcmp(get_list_element(head, i) -> dat -> str1, get_list_element(head, i+1) -> dat -> str1) > 0) { 
				swap(head, i, i+1); 
			}
		}
	}
}

void dsort_str1(ListNode ** head) { 
    int num = 0;
	num = cnt_lst(head); 
	for(num; num>=2; num--){
		for(int i=0; i<num-1; i++) {
			if(strcmp(get_list_element(head, i) -> dat -> str1, get_list_element(head, i+1) -> dat -> str1) < 0) { 
				swap(head, i, i+1); 
			}
		}
	}
}

void asort_str2(ListNode ** head) { 
    int num = 0; 
	num = cnt_lst(head); 
	for(num; num>=2; num--){
		for(int i=0; i<num-1; i++) {
			if(strcmp(get_list_element(head, i) -> dat -> str2, get_list_element(head, i+1) -> dat -> str2) > 0) { 
				swap(head, i, i+1); 
			}
		}
	}
}

void dsort_str2(ListNode ** head) { 
    int num = 0; 
	num = cnt_lst(head); 
	for(num; num>=2; num--){
		for(int i=0; i<num-1; i++) {
			if(strcmp(get_list_element(head, i) -> dat -> str2, get_list_element(head, i+1) -> dat -> str2) < 0) { 
				swap(head, i, i+1); 
			}
		}
	}
}

void balance(Node ** root, ListNode ** head, Node * node) { 
	Node * fat = node -> prv; 
	asort_id(head); 
	Node * sml_node = get_list_element(head, 0) -> dat; 
	Node * med_node = get_list_element(head, 1) -> dat; 
	Node * bgs_node = get_list_element(head, 2) -> dat; 
	if(fat != NULL) { 
		(strcmp(node -> id, fat -> id) > 0) ? (fat -> rgt = med_node) : (fat -> lft = med_node);
		med_node -> prv = fat; 
	} else { 
		(* root) = med_node; 
		med_node -> prv = NULL; 
	}

    Node * tmp_lft = med_node -> lft; 
    if(tmp_lft != NULL && tmp_lft != sml_node) {
        sml_node -> rgt = tmp_lft;
        tmp_lft -> prv = sml_node;
    }
    else if(sml_node -> rgt == med_node || sml_node -> rgt == bgs_node) {
        sml_node -> rgt = NULL;
    }

    Node * tmp_rgt = med_node -> rgt;
    if(med_node -> rgt != NULL && med_node -> rgt != bgs_node) {
        bgs_node -> lft = tmp_rgt;
        tmp_rgt -> prv = bgs_node;
    }
    else if(bgs_node -> lft == sml_node || bgs_node -> lft == med_node) {
        bgs_node -> lft = NULL;
    }

    med_node -> lft = sml_node;
    med_node -> rgt = bgs_node;
    sml_node -> prv = med_node;
    bgs_node -> prv = med_node;
}

void check_balance(Node ** root, Node * node) { 
	ListNode * head = NULL; 
	while(node) { 
		queue(&head, mk_list_node(node)); 
		if(cnt_lst(&head) > 3) 
			dequeue(&head); 
		if(abs(height(node -> lft) - height(node -> rgt)) > 1) {
			balance(root, &head, node); 
			node = NULL;  
		}
		if(node) { 
			node = node -> prv; 		
		}
	}
}

void traverse(Node ** root, Node * fat_node, Node * node) { 
	int bgst_val = (strcmp(node -> id, fat_node -> id) > 0 ) ? 1 : 0; 
	switch(bgst_val) { 	
		case 1: if(fat_node -> rgt) 
					traverse(root, fat_node -> rgt, node); 
				else {
					fat_node -> rgt = node;
					fat_node -> rgt -> prv = fat_node; 
					check_balance(root, fat_node -> rgt);  
				}
				break; 
		case 0: if(fat_node -> lft)
					traverse(root, fat_node -> lft, node); 
				else { 
					fat_node -> lft = node; 
					fat_node -> lft -> prv = fat_node;
					check_balance(root, fat_node -> lft); 
				}
	}
}

void insrt(Node ** root, ListNode ** head, Node * node) {
    if((* root) == NULL) {
		(* root) = node;
        queue(head, mk_list_node(node)); 
    }
	else {
		if(srch_id(root, node -> id) == NULL) {
            queue(head, mk_list_node(node)); 
			traverse(root, (* root), node); 
		} else 
			printf("\nId already exists\n");
	}
}

void insrt_menu(Node ** root, ListNode ** head) {	
	Node * tmp; 
    char * id = malloc(sizeof((char)(MAX_SIZE))); 
    char * str1 = malloc(sizeof((char)(MAX_SIZE)));
    char * str2 = malloc(sizeof((char)(MAX_SIZE)));
    printf("id: "); 
    fgets(id, MAX_SIZE-1, stdin); 
    printf("str1: "); 
    fgets(str1, MAX_SIZE-1, stdin); 
    printf("str2: "); 
    fgets(str2, MAX_SIZE-1, stdin); 
    printf("\n");
	tmp = mk_node(id, str1, str2); 
    insrt(root, head, tmp); 
}

void dequeue_with_num(ListNode ** head, int num) { 
    ListNode * tmp = (* head); 
    ListNode * prv = NULL; 
    int is_found = 0;  
    int cnt = 0;
    while(num>cnt) { 
        tmp = tmp -> nxt; 
        cnt++; 
    }
    if(cnt == 0) { 
        (* head) = tmp -> nxt; 
    }
    else if(get_list_element(head, cnt-1) != NULL) { 
        prv = get_list_element(head, cnt-1); 
        prv -> nxt = tmp -> nxt; 
    }
    cln_list_node(tmp); 
    free(tmp); 
}

void del_list_node(ListNode ** head, char * id_to_del) { 
    int is_node; 
    for(int i=0; i<cnt_lst(head); i++) { 
        if(strcmp(get_list_element(head, i) -> dat -> id, id_to_del) == 0) {
            dequeue_with_num(head, i); 
        }
    }
}

void del_node(Node ** root, ListNode ** head, char * id_to_del) { 
    Node * tmp; 
    char * op = malloc(sizeof( (char)(MAX_SIZE) )); 
    tmp = srch_id(root, id_to_del); 
    if( (tmp != NULL) && (tmp -> is_available > 0) ) { 
        printf("Node to delete: %s", id_to_del); 
        printf("Y/N: "); 
        fgets(op, MAX_SIZE-1, stdin); 
        if(strcmp(op, "Y\n") == 0 || strcmp(op, "y\n")) {
            del_list_node(head, id_to_del); 
            tmp -> is_available = 0; 
            printf("The operation was successful\n");
        }
    }
    else
        printf("Id not available\n"); 
}

void del_menu(Node ** root, ListNode ** head) { 
    char * id_to_del = malloc(sizeof((char)(MAX_SIZE))); 
    printf("Enter the id to delete: "); 
    fgets(id_to_del, MAX_SIZE-1, stdin); 
    del_node(root, head, id_to_del); 
}

void edit(Node ** root, char * id_to_edit) { 
    Node * tmp = srch_id(root, id_to_edit); 
    if( (tmp != NULL) && (tmp -> is_available > 0) ) { 
        printf("Current str1 on the node: %s", tmp -> str1); 
        printf("Current str2 on the node: %s", tmp -> str2);
        printf("Enter the new value for str1: "); 
        fgets(tmp -> str1, MAX_SIZE-1, stdin); 
        printf("Enter the new value for str2: ");
        fgets(tmp -> str2, MAX_SIZE-1, stdin);
        printf("\n");
    }
    else 
        printf("id not available\n");  
}

void edit_menu(Node ** root) { 
    char * id_to_edit = malloc(sizeof((char)(MAX_SIZE)));  
    printf("Enter the id to edit: "); 
    fgets(id_to_edit, MAX_SIZE-1, stdin); 
    edit(root, id_to_edit);
}

void recover(Node ** root, ListNode ** head, char * id_to_rcvr) { 
    Node * tmp = srch_id(root, id_to_rcvr); 
    if(tmp != NULL) { 
        if(tmp -> is_available == 1) {  
            printf("You cannot recover an active node\n"); 
        }
        else { 
            tmp -> is_available = 1; 
            queue(head, mk_list_node(tmp));
            printf("The operation was successful\n"); 
        }
    }
    else
        printf("Id is not available\n"); 
}

void recover_menu(Node ** root, ListNode ** head) { 
    char * id_to_rcvr = malloc(sizeof((char)(MAX_SIZE)));
    printf("Enter the id to recover: "); 
    fgets(id_to_rcvr, MAX_SIZE-1, stdin); 
    recover(root, head, id_to_rcvr);
}

void total_rep_menu(ListNode ** head) { 
    int int_opt;
    char * str_opt = malloc(sizeof((char)(MAX_SIZE))); 
    printf("Please, choose a print order\n1. Ascending order by id\n2. Descending order by id\n3. Ascending order by str1\n4. Descending order by str1\n5. Ascending order by str2\n6. Descending order by str2\n");  
    fgets(str_opt, MAX_SIZE-1, stdin); 
    int_opt = atoi(str_opt); 
    printf("You selected: %d\n", int_opt); 
    switch(int_opt) {
        case 1: 
            asort_id(head); 
            pnt_lst((* head));
            break;
        case 2: 
            dsort_id(head);
            pnt_lst((* head));
            break;
        case 3: 
            asort_str1(head);
            pnt_lst((* head));               
            break;
        case 4: 
            dsort_str1(head);
            pnt_lst((* head));
            break;
        case 5: 
            asort_str2(head);
            pnt_lst((* head));
            break;
        case 6: 
            dsort_str2(head);
            pnt_lst((* head));
            break; 
        default: 
            printf("You didn't enter a valid option\n"); 
            break; 
    }
}

void srch_id_exact_match_menu(Node ** root) { 
    Node * tmp; 
    char * val_to_search = malloc(sizeof((char)(MAX_SIZE)));
    printf("Enter the value to search: \n"); 
    fgets(val_to_search, MAX_SIZE-1, stdin); 
    tmp = srch_id(root, val_to_search); 
    if(tmp == NULL) 
        printf("The value was not found\n"); 
    else { 
        printf("The value was found in the following node:\n"); 
        pnt_node(tmp);         
    }
}

void pnt_smllr_or_equal_id(ListNode ** head, char * srch_val) { 
    ListNode * tmp = (* head); 
    while(tmp) { 
        if(strcmp(tmp -> dat -> id, srch_val) <= 0) 
            pnt_node(tmp -> dat); 
        tmp = tmp -> nxt;
    }
}

void pnt_smaller_or_equal_menu(ListNode ** head) { 
    Node * tmp; 
    char * val_to_search = malloc(sizeof((char)(MAX_SIZE)));
    printf("Enter the value to search: \n"); 
    fgets(val_to_search, MAX_SIZE-1, stdin); 
    printf("Nodes found with results smaller or equal to your value:\n"); 
    pnt_smllr_or_equal_id(head, val_to_search);        
}

void pnt_greater_or_equal_id(ListNode ** head, char * srch_val) { 
    ListNode * tmp = (* head); 
    while(tmp) { 
        if(strcmp(tmp -> dat -> id, srch_val) >= 0) 
            pnt_node(tmp -> dat); 
        tmp = tmp -> nxt;
    }
}

void pnt_greater_or_equal_menu(ListNode ** head) { 
    Node * tmp; 
    char * val_to_search = malloc(sizeof((char)(MAX_SIZE)));
    printf("Enter the value to search: \n"); 
    fgets(val_to_search, MAX_SIZE-1, stdin); 
    printf("Nodes found with results greater or equal to your value:\n"); 
    pnt_greater_or_equal_id(head, val_to_search);        
}

void exact_str_fld_srch(ListNode ** head, char * srch_val) { 
    ListNode * tmp = (* head); 
    while(tmp) { 
        if( (strcmp(tmp -> dat -> str1, srch_val) == 0) ||  (strcmp(tmp -> dat -> str2, srch_val) == 0)) 
            pnt_node(tmp -> dat); 
        tmp = tmp -> nxt;
    }   
}

void exact_str_fld_srch_menu(ListNode ** head) { 
    Node * tmp; 
    char * val_to_search = malloc(sizeof((char)(MAX_SIZE)));
    printf("Enter the value to search: \n"); 
    fgets(val_to_search, MAX_SIZE-1, stdin); 
    printf("The values found for your search are: \n"); 
    exact_str_fld_srch(head, val_to_search); 
}

char * cln_str(char * str) { 
    char * tmp = malloc(sizeof((char)(MAX_SIZE)));
    strcpy(tmp, str);
    int n = strlen(tmp); 
    if(n>0) 
        if(tmp[strlen(tmp)-1] == '\n') 
            tmp[strlen(tmp)-1] = 0; 
    return tmp;
}

void substring_srch(ListNode ** head, char * srch_val) { 
    ListNode * tmp = (* head); 
    while(tmp) { 
        if(strstr(cln_str(tmp -> dat -> str1), cln_str(srch_val)) != NULL) {  
            printf("\nFound coincidence in str1:\n");
            pnt_node(tmp -> dat); 
        }
        if(strstr(cln_str(tmp -> dat -> str2), cln_str(srch_val)) != NULL) { 
            printf("\nFound coincidence in str2:\n");
            pnt_node(tmp -> dat); 
        }
        tmp = tmp -> nxt;
    }     
}

void substring_srch_menu(ListNode ** head) { 
    Node * tmp; 
    char * val_to_search = malloc(sizeof((char)(MAX_SIZE)));
    printf("Enter the value to search: \n"); 
    fgets(val_to_search, MAX_SIZE-1, stdin); 
    substring_srch(head, val_to_search); 
}

void srch_id_submenu(Node ** root, ListNode ** head) { 
    char * str_opt = malloc(sizeof((char)(MAX_SIZE)));
    int int_opt;
    printf("\n1. Exact match\n2. Values lesser or equal to id\n3. Values greater or equal to id\n"); 
    fgets(str_opt, MAX_SIZE-1, stdin); 
    int_opt = atoi(str_opt); 
    printf("You selected: %d\n", int_opt); 
    switch(int_opt) { 
        case 1: 
            srch_id_exact_match_menu(root); 
            break;
        case 2: 
            pnt_smaller_or_equal_menu(head); 
            break; 
        case 3: 
            pnt_greater_or_equal_menu(head);  
            break;
        default: 
            printf("Please, select a valid option\n"); 
            break; 
    }
}

void srch_on_fields_submenu(ListNode ** head) {
    char * str_opt = malloc(sizeof((char)(MAX_SIZE)));
    int int_opt;
    printf("\n1. Exact match\n2. Substring\n"); 
    fgets(str_opt, MAX_SIZE-1, stdin); 
    int_opt = atoi(str_opt);
    switch(int_opt) { 
        case 1: 
            exact_str_fld_srch_menu(head); 
            break; 
        case 2: 
            substring_srch_menu(head); 
            break;
        default: 
            printf("Please, select a valid option\n"); 
            break; 
        }
}

void search_menu(Node ** root, ListNode ** head) { 
    int int_opt;
    char * str_opt = malloc(sizeof((char)(MAX_SIZE))); 
    printf("1. Look for an id\n2. Look for a string (in the other two fields)\n"); 
    fgets(str_opt, MAX_SIZE-1, stdin); 
    int_opt = atoi(str_opt); 
    printf("You selected: %d\n", int_opt); 
    switch(int_opt) { 
        case 1: 
            srch_id_submenu(root, head); 
            break;
        case 2: 
            srch_on_fields_submenu(head); 
            break;
        default: 
            printf("Please, choose a valid option\n"); 
    }
}

void save_back(Node ** root, char * file_name) { 
    FILE * ptf = NULL; 
    ListNode * head = NULL; 
    ListNode * lst_tmp = NULL; 
    dfs_lst(&head, (*root)); 
    ptf = fopen(file_name, "w"); 
    while(cnt_lst(&head) > 0) { 
        lst_tmp = dequeue(&head); 
        fprintf(ptf, "%s", lst_tmp -> dat -> id);
        fprintf(ptf, "%s", lst_tmp -> dat -> str1);
        fprintf(ptf, "%s", lst_tmp -> dat -> str2);
        lst_tmp = NULL;
    }
    fclose(ptf); 
}

void load_back(Node ** root, ListNode ** head, char * file_name) { 
    (* root) = NULL; 
    (* head) = NULL;
    int cnt = 0;
    FILE * ptf; 
    char * tmp_id;
    char * tmp_str1;
    char * tmp_str2;
    char * tmp_str = malloc(sizeof((char)(MAX_SIZE)));
    strtok(file_name, "\n");
    ptf = fopen(file_name, "r");
    if(ptf != NULL) { 
        while(fgets(tmp_str, MAX_SIZE-1, ptf) != NULL) { 
            cnt++; 
            if(cnt == 1) {    
                tmp_id = malloc(sizeof((char)(MAX_SIZE)));
                strcpy(tmp_id, tmp_str); 
            }
            if(cnt == 2) {  
                tmp_str1 = malloc(sizeof((char)(MAX_SIZE)));
                strcpy(tmp_str1, tmp_str); 
            }
            if(cnt == 3) {
                tmp_str2 = malloc(sizeof((char)(MAX_SIZE)));
                strcpy(tmp_str2, tmp_str); 
                cln_str(tmp_str2);
                cnt = 0;
                insrt(root, head, mk_node(tmp_id, tmp_str1, tmp_str2)); 
                tmp_id = '\0';
                tmp_str1 = '\0';
                tmp_str2 = '\0';
                tmp_str = '\0';
                tmp_str = malloc(sizeof((char)(MAX_SIZE)));
            }
        }
        fclose(ptf);
    } else 
        printf("File not found\n"); 
}

void save_back_menu(Node ** root) { 
    int int_opt;
    char * str_opt = malloc(sizeof((char)(MAX_SIZE))); 
    printf("Enter the name of the new text file: "); 
    fgets(str_opt, MAX_SIZE-1, stdin); 
    str_opt = cln_str(str_opt);
    save_back(root, str_opt); 
}

void load_back_menu(Node ** root, ListNode ** head) { 
    int int_opt;
    char * str_opt = malloc(sizeof((char)(MAX_SIZE))); 
    char * str_opt2 = malloc(sizeof((char)(MAX_SIZE)));
    printf("Enter the name of the backup: "); 
    fgets(str_opt, MAX_SIZE-1, stdin); 
    printf("Your current data is going to be deleted\nContinue? Y/N: "); 
    fgets(str_opt2, MAX_SIZE-1, stdin); 
    if(strcmp(str_opt2, "Y\n") == 0 || strcmp(str_opt2, "y\n") == 0) {
        load_back(root, head, str_opt); 
    }
}

void admin_tools_menu(Node ** root, ListNode ** head) { 
    int int_opt;
    char * str_opt = malloc(sizeof((char)(MAX_SIZE))); 
    printf("1. Save a backup of the information\n2. Load data from a backup file\n"); 
    fgets(str_opt, MAX_SIZE-1, stdin); 
    int_opt = atoi(str_opt); 
    printf("You selected: %d\n", int_opt); 
    switch(int_opt) { 
        case 1: save_back_menu(root); 
            break;
        case 2: load_back_menu(root, head); 
            break; 
    }
    
}

void auto_back(Node ** root, int is_dat) { 
    if((* root) != NULL)
        if(!is_dat) 
            save_back(root, "data.txt");  
}

void data_menu(int is_dat) { 
   if(is_dat<1) 
        printf("\nNo data found, creating a new data.txt file\n"); 
}

int check_for_data() { 
    FILE * ptf = fopen("data.txt", "r");   
    if(ptf == NULL) 
        return 0; 
    return 1; 
}

void main() { 
    int is_dat = 0;
    int int_op = 0;
    int is_fin = 0; 
    char * str_op; 
    Node * root = NULL; 
    ListNode * head = NULL; 
    str_op = malloc(sizeof((char)(MAX_SIZE)));
    is_dat = check_for_data(); 
    data_menu(is_dat); 
    while(!is_fin) { 
        printf("\n1. Insert a new entity\n2. Delete an entity\n3. Edit an entity\n4. Recover a deleted entity\n6. Total Report\n7. Search\n9. Administrative Tools\n0. Exit\n");    
        fgets(str_op, MAX_SIZE-1, stdin); 
        int_op = atoi(str_op); 
        printf("\nYou selected: %d\n", int_op);
        switch(int_op) { 
            case 1: 
                insrt_menu(&root, &head); 
                break;
            case 2: 
                del_menu(&root, &head); 
                break;
            case 3: 
                edit_menu(&root); 
                break;
            case 4: 
                recover_menu(&root, &head); 
                break;
            case 6: 
                total_rep_menu(&head); 
                break;
            case 7: 
                search_menu(&root, &head);
                break;
            case 9: 
                admin_tools_menu(&root, &head);
                break;
            case 0: 
                auto_back(&root, is_dat); 
                is_fin = 1; 
                break; 
            default: 
                printf("\nPlease, enter a valid option\n"); 
                break;
        }
    }
}
