#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void xor(int [],int [16][4],int);
void sbox_f(int [1][4],int );
void ddt();
void probability();


int delta_X[16][4]= {{0,0,0,0},{0,0,0,1},{0,0,1,0},{0,0,1,1},{0,1,0,0},{0,1,0,1},{0,1,1,0},{0,1,1,1},{1,0,0,0},
		    {1,0,0,1},{1,0,1,0},{1,0,1,1},{1,1,0,0},{1,1,0,1},{1,1,1,0},{1,1,1,1}};//predefined 0 to 15

int sbox[16][4]= {{1,1,1,0},{0,1,0,0},{1,1,0,1},{0,0,0,1},{0,0,1,0},{1,1,1,1},{1,0,1,1},{1,0,0,0},{0,0,1,1},
		  {1,0,1,0},{0,1,1,0},{1,1,0,0},{0,1,0,1},{1,0,0,1},{0,0,0,0},{0,1,1,1}};//output of s-box

int array[4],array1[4],array2[4],row=0,a=0,col1=0,row1=0,Z[4],a1=0,a2=0;
int X_dash[16][4],Y[16][4],X_star[16][16][4],Y_star[16][16][4],Y_dash[16][16][4],table[16][16];
double probab[16][16];

void main()
{	int i,j,k;
	int X[16][4]= {{0,0,0,0},{0,0,0,1},{0,0,1,0},{0,0,1,1},{0,1,0,0},{0,1,0,1},{0,1,1,0},{0,1,1,1},
		      {1,0,0,0},{1,0,0,1},{1,0,1,0},{1,0,1,1},{1,1,0,0},{1,1,0,1},{1,1,1,0},{1,1,1,1}};
	int temp[1][4],temp1[4];
							// calculating X star
	for(i=0;i<16;i++) {
	    for(j=0;j<4;j++) {
		array[a++]=delta_X[i][j];
	    }
	    xor(array,X,i);
	    a=0;
	
	}
	/*printf("\n\n\t\t----X star table-----\n");//printing X star table
	for(i=0;i<16;i++) {
	    for(j=0;j<16;j++) {
	        for(k=0;k<4;k++) {
		    printf("%d ",X_star[i][j][k]);
		}
		printf("\n");
	    }
	printf("\n\n");
	}*/
	
                                          	// Calculating Y table
	for(i=0;i<16;i++) {
	    for(j=0;j<4;j++) {
		temp[0][j]=delta_X[i][j];
	    }
	    sbox_f(temp,1);                     //function call to sbox
	}
	/*printf("\t\t----Y table---\n");		// printing Y table
	for(j=0;j<16;j++) {
	        for(k=0;k<4;k++) {
		    printf("%d ",Y[j][k]);
		}
		printf("\n");
	}*/
                           	           	//Calculating Y star table
	for(i=0;i<16;i++) {
	    for(j=0;j<16;j++) {
	        for(k=0;k<4;k++) {
		    temp[0][k]=X_star[i][j][k];
		}
		sbox_f(temp,0);               //function call to sbox
	    }
	    col1++;
	    row1=0;
	}
	    
	/*printf("\n\n\t\t----Y star table-----\n");//printing Y star table
	for(i=0;i<16;i++) {
	    for(j=0;j<16;j++) {
	        for(k=0;k<4;k++) {
		    printf("%d ",Y_star[i][j][k]);
		}
		printf("\n");
	    }
	printf("\n\n");
	}
	*/						//Calculating Y dash
	for(i=0;i<16;i++) {
	    for(j=0;j<16;j++) {
	        for(k=0;k<4;k++) {
		    Y_dash[i][j][k]=Y[j][k]^Y_star[i][j][k];
		}
	    }
	}
	/*printf("\n\n\t\t----Y dash table-----\n");     //printing Y dash table
	for(i=0;i<16;i++) {
	    for(j=0;j<16;j++) {
	        for(k=0;k<4;k++) {
		    printf("%d ",Y_dash[i][j][k]);
		}
		printf("\n");
	    }
	printf("\n\n");
	}*/
	ddt();                                          // function call ddt
	printf("\n\n\t\t------- DDT Table -------\n\n"); // printing DDT table
	for(i=0;i<16;i++) {
	    for(j=0;j<16;j++) {
	        printf("%d   ",table[i][j]);

	    }
	printf("\n\n");
	}
	probability();
	printf("\n\n\t\t------- Probability Table -------\n\n"); 
        for(i=0;i<16;i++) {
	    for(j=0;j<16;j++) {
	        printf("%f ",probab[i][j]);

	    }
	printf("\n\n");
	}
}

void xor(int array[4],int X[16][4],int h)
{	int i,j,k,c=0;
	int temp[1][4];
	
	for(i=0;i<16;i++) {
            for(j=0;j<4;j++) {
                array1[a1++]=X[i][j];
            }
            for(k=0;k<4;k++){
		if(array[k]==array1[k])
		    array2[a2++]=0;
		else
		    array2[a2++]=1;
	    }
	    for(k=0;k<4;k++){
		X_dash[i][c++]=array2[k];
	    }
	    c=0,a2=0,a1=0;
        }	
	for(i=0;i<16;i++) {
            for(j=0;j<4;j++) {
		X_star[h][i][j]=X_dash[i][j];
		
		
	    }
	 	
	}
	
}

void sbox_f(int X[1][4],int flag)// s-box implementation 
{
        int i,j,k,l,m,sum=0,col=0,n=3;
       
	    for(j=0;j<4;j++){
		sum = sum + (X[0][j]*pow(2,n)); //take binary no and convert it into decimal
	            if (n==0) {
//        	        printf("sum=%d\n",sum);
  //                  printf("sbox_4bits=");
                    for(m=0;m<4;m++)
		        Z[col++]=sbox[sum][m];
                    //printf("%d",sbox[sum][m]);
                    }   
             	    else 
                         n--;
             	    
            }
	    if(flag==1) {
	        for(j=0;j<4;j++) {
		
                    Y[row][j]=Z[j];
                }
	        row++;
	    }
	    else {
	            for(k=0;k<4;k++) {
			Y_star[col1][row1][k]=Z[k];
		    }
		row1++;
	        
	    }
}

void ddt()
{
	int temp1[4],i,j,k,m,n,temp2[4],count=0,flag=0;
	for(i=0;i<16;i++) {
            for(j=0;j<4;j++) {
		temp1[j]=delta_X[i][j];
	    }
	    for(k=0;k<16;k++) {
		for(m=0;m<16;m++) {
                    for(n=0;n<4;n++) {
		        temp2[n]=Y_dash[k][m][n];
	            }
		    for(j=0;j<4;j++) {
		        if(temp1[j]==temp2[j])
			    continue;
		    	else {
			    flag=1;
			    break;
		        }
		    }
		    if(flag==0){
		    	table[k][i]=++count;
		    }
		flag=0;
		    
		}
		
		count=0;
		flag=0;
	    }
	}
		    
}
void probability()
{
    int k,m;
    for(k=0;k<16;k++) {
	for(m=0;m<16;m++) {
	    probab[k][m]=(float)table[k][m]/16;	
	}
    }

}
