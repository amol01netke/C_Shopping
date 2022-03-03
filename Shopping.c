#include<stdio.h>
#include<malloc.h>

int productNumber[5]={1,2,3,4,5};
char productName[5][15]={"Hair oil","Toothpaste","Toothbrush","Handwash","Facewash"};
int productCost[5]={30,50,20,60,90};
int productAvailable[5]={30,30,30,30,30};

struct Node{
	int data;
	struct Node *next;
};

struct Node *productNumberHead,*productNumberTail;
struct Node *quantityHead,*quantityTail;
struct Node *totalCostHead,*totalCostTail;

struct Node *createNode(int data){
	struct Node *newNode=(struct Node*)malloc(sizeof(struct Node));
	newNode->data=data;
	newNode->next=NULL;
	return newNode;
}

void appendProductNumberNode(struct Node *productNumberNode){
	if(!productNumberHead){
		productNumberHead=productNumberNode;
		productNumberTail=productNumberNode;
	}
	else{
		productNumberTail->next=productNumberNode;
		productNumberTail=productNumberTail->next;
	}
}

void appendQuantityNode(struct Node *quantityNode){
	if(!quantityHead){
		quantityHead=quantityNode;
		quantityTail=quantityNode;
	}
	else{
		quantityTail->next=quantityNode;
		quantityTail=quantityTail->next;
	}
}

void appendTotalCostNode(struct Node *totalCostNode){
	if(!totalCostHead){
		totalCostHead=totalCostNode;
		totalCostTail=totalCostNode;
	}
	else{
		totalCostTail->next=totalCostNode;
		totalCostTail=totalCostTail->next;
	}
}

void printProductMenu(){
	printf("\n---Product Menu---");
	printf("\nNo.\t|Name\t\t|Cost\t|Available");
	for(int i=0;i<5;i++){
		printf("\n%d\t|%s\t|%d\t|%d",productNumber[i],productName[i],productCost[i],productAvailable[i]);
	}
}

int isProductNumberInvalid(int productNumber){
	return productNumber<1 || productNumber>5;
}

int isQuantityInvalid(int quantity){
	return quantity<0 || quantity>5;
}

int isProductUnavailable(int productNumber,int quantity){
	return productAvailable[productNumber-1]<quantity;
}

void updateQuantity(int productNumber,int quantity){
	productAvailable[productNumber-1]-=quantity;
}

int calculateGrandTotal(){
	struct Node *ptr=totalCostHead;
	int grandTotal=0;
	while(ptr!=NULL){
		grandTotal+=ptr->data;
		ptr=ptr->next;
	}
	return grandTotal;
}

void printInvoice(){
	struct Node *ptr1=productNumberHead;
	struct Node *ptr2=quantityHead;
	struct Node *ptr3=totalCostHead;

	printf("\n---Invoice---");
	printf("\nNo.\t|Name\t\t|Cost\t|Quantity\t|Total cost");
	while(ptr1!=NULL){
		printf("\n%d\t|%s\t|%d\t|%d\t\t|%d",ptr1->data,productName[ptr1->data-1],productCost[ptr1->data-1],ptr2->data,ptr3->data);
		ptr1=ptr1->next;
		ptr2=ptr2->next;
		ptr3=ptr3->next;	
	}
	printf("\n-----------------------------------------------------------");
	printf("\nGrand total\t\t\t\t\t|%d",calculateGrandTotal());
}

int main(){
	int productNumber,quantity,totalCost,conitnueOrNot;
	struct Node *productNumberNode,*quantityNode,*totalCostNode;

	//repeat the loop until the customer wishes to stop
	while(1){
		//print the menu of products
		printProductMenu();

		//read a product number from the customer
		get_product_number:
			printf("\nEnter a product number:");
			scanf("%d",&productNumber);
		
		if(isProductNumberInvalid(productNumber)){
			printf("\nInvalid input!");
			goto get_product_number;
		}
		
		//read the quantity of the product from the customer
		get_quantity:
			printf("\nEnter quantity(Maximum 5 at one time!):");
			scanf("%d",&quantity);
		
		if(isQuantityInvalid(quantity)){
			printf("\nInvalid input!");
			goto get_quantity;
		}
		
		if(isProductUnavailable(productNumber,quantity)){
			printf("\nSorry,this product is no more available!");
			goto get_product_number;
		}

		//update the quantity every time
		updateQuantity(productNumber,quantity);
		
		//calculate total cost as per the quantity
		totalCost=productCost[productNumber-1]*quantity;
		
		//create specfic nodes for each data we get from the user
		productNumberNode=createNode(productNumber);
		quantityNode=createNode(quantity);
		totalCostNode=createNode(totalCost);
		
		//append the nodes specifically
		appendProductNumberNode(productNumberNode);
		appendQuantityNode(quantityNode);
		appendTotalCostNode(totalCostNode);
	
		printf("\nPress 0 if you want to continue:");
		scanf("%d",&conitnueOrNot);
		if(conitnueOrNot!=0)
			break;
	}	

	//print the invoice
	printInvoice();
	return 0;
}
