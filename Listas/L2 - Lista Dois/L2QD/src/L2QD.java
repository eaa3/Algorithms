

class Node {
	
	public int n;
	public int[] chave;
	public Node[] pont;
	
	public Node(int d)
	{
		//Só utilizo somente 2d chaves, a outra é utilizada temporariamente nos splits, a 0 não é usada
		this.chave = new int[2*d + 2];
		//Utilizo utlizo somente 2*d + 1 apontadores o outro é utilizado temporáriamente nos splits
		this.pont = new Node[this.chave.length];
		
		this.n = 0;
	}
	
	public void add(int chave)
	{
		this.chave[++this.n] = chave;
	}
	
	public void addEntrada(int chave,Node pont)
	{
		this.chave[++this.n] = chave;
		this.pont[this.n] = pont;
		
	}
	
	
	public void ordenar()
	{
		int temp;
		Node tempPont;
		
		for(int i=1; i<=n-1 ;i++)
		{
			for(int j=i+1; j<= n; j++)
			{
				if( this.chave[j] <= this.chave[i] )
				{
					temp = this.chave[i];
					tempPont = this.pont[i];
					
					this.pont[i] = this.pont[j];
					this.pont[j] = tempPont;
					
					this.chave[i] = this.chave[j];
					this.chave[j] = temp;
				}
					
			}
		}
	}
	
	
	

}

class Info {
	
	public Info()
	{
		
	}
	
	//Pagina onde ocorreu a inserção
	public Node pag;
	
	//Local onde ocorreu a inserção
	public int loc;
	
	//Bool que indica se ocorreu split ou não na página inserida
	public boolean split;
	
	//Bool que indica, no método de busca, se a chave foi encontrada ou não
	public boolean found;
	
	//Entrada à ser adicionada no pai, por causa do split
	public int chave;
	public Node pt1;
	

}


class BTree {
	
	public Node raiz;

	//Ordem
	public int d;

	public BTree(int ordem)
	{
		this.d = ordem;
	}


	public boolean isLeaf(Node pagina)
	{
		boolean leaf = true;
		int k = 0;
		while(leaf && k <= pagina.n)
		{
			leaf = (pagina.pont[k] == null);
			k++;
		}

		return leaf;
	}
	
	public void printItOrdem(Node raiz,int nivel)
	{
		if( this.isLeaf(raiz) )
		{
			
			for(int i=1; i<=raiz.n; i++)
			{
				for(int j=0; j<nivel ;j++) L2QD.output.append("----");
				L2QD.output.append(raiz.chave[i]).append(System.getProperty("line.separator"));
			}
		}
		else
		{
			for(int i=0; i <= raiz.n; i++)
			{
				printItOrdem(raiz.pont[i],nivel + 1);
				if(i < raiz.n ) {
					for(int j=0; j<nivel ;j++) L2QD.output.append("----");
					L2QD.output.append(raiz.chave[i + 1]).append(System.getProperty("line.separator"));				
				}
			}
			
		}
	}

	public Info split(Node pagina)
	{
		Info infOut = new Info();

		if( pagina == this.raiz )
		{
			//Nova raiz
			infOut.pag = new Node(this.d);

			Node pt1 = new Node(this.d);

			for( int i=(d+2) ; i<=pagina.n ; i++ )
			{
				pt1.addEntrada(pagina.chave[i],pagina.pont[i]);
				pagina.chave[i] = 0;
				pagina.pont[i] = null;
			}
			
			pt1.pont[0] = pagina.pont[this.d + 1];
			pagina.pont[this.d + 1] = null;

			infOut.pag.add(pagina.chave[this.d + 1]);
			pagina.chave[this.d + 1] = 0;

			pagina.n -= d+1;

			infOut.pag.pont[0] = pagina;
			infOut.pag.pont[1] = pt1;

		}
		else
		{
			infOut.pag = pagina;
			
			Node pt1 = new Node(this.d);

			for( int i=(d+2) ; i<=pagina.n ; i++ )
			{
				pt1.addEntrada(pagina.chave[i],pagina.pont[i]);
				pagina.chave[i] = 0;
				pagina.pont[i] = null;
			}
			pt1.pont[0] = pagina.pont[this.d + 1];
			pagina.pont[this.d + 1] = null;
			
			infOut.chave = pagina.chave[this.d + 1];
			pagina.chave[this.d + 1] = 0;
			
			infOut.pt1 = pt1;

			pagina.n -= d+1;
			
		}

		return infOut;
	}

	public boolean inserir(int chave)
	{
		this.raiz = this.inserir(this.raiz,chave).pag;

		return true;
	}

	public Info inserir(Node pagina, int chave)
	{

		Info infIn = new Info();
		Info infOut = new Info();

		if(pagina == null)
		{
			infOut.pag = new Node(this.d);
			infOut.pag.add(chave);
		}
		else
		{
			infOut.pag = pagina;

			int k = 1;

			while( k < pagina.n && chave > pagina.chave[k] )
			{
				k++;
			}

			//Inserção ilegal
			if(chave == pagina.chave[k])
			{

			}
			else if( chave < pagina.chave[k] )
			{
				if( !this.isLeaf(pagina) )
				{
					infIn = this.inserir(pagina.pont[k - 1], chave);

					pagina.pont[k - 1] = infIn.pag;

					if( infIn.split ) 
					{
						pagina.addEntrada(infIn.chave,infIn.pt1);
						pagina.ordenar();

						if( pagina.n > 2*this.d)
						{
							infOut = this.split(pagina);
							infOut.split = true;
						}

					}

				}
				else
				{
					pagina.add(chave);
					pagina.ordenar();

					infOut.split = false;

					if( pagina.n > 2*this.d )
					{
						infOut = this.split(pagina);
						infOut.split = true;
					}
				}

			}
			else
			{
				if( !this.isLeaf(pagina) )
				{
					infIn = this.inserir(pagina.pont[k], chave);

					pagina.pont[k] = infIn.pag;

					if( infIn.split ) 
					{
						pagina.addEntrada(infIn.chave,infIn.pt1);
						pagina.ordenar();

						if( pagina.n > 2*this.d)
						{
							infOut = this.split(pagina);
							infOut.split = true;
						}

					}

				}
				else
				{
					pagina.add(chave);
					pagina.ordenar();

					infOut.split = false;

					if( pagina.n > 2*this.d )
					{
						infOut = this.split(pagina);
						infOut.split = true;
					}
				}

			}

		}

		return infOut;
	}
	
	

}

public class L2QD
{
	public static Arquivo arq = new Arquivo("L2QD.in","L2QD.out");
	
	public static StringBuffer output = null;
	
	public static void main(String args[])
	{
		BTree btree = null;
		int N = 0;
		int bufInt = 0;
		int countConj = 0;
		
		while( !L2QD.arq.isEndOfFile() )
		{
			btree = new BTree(5);
			output = new StringBuffer();
			N = arq.readInt();
			
			for(int i=0; i<N ; i++)
			{
				bufInt = arq.readInt();
				btree.inserir(bufInt);
			}
			
			output.append("Conjunto #").append(++countConj).append(System.getProperty("line.separator"));
			btree.printItOrdem(btree.raiz,0);
			output.append(System.getProperty("line.separator"));
			
			arq.print(output.toString());
			
			btree = null;
			output = null;
		}
		
		
		arq.close();
		
	}
	
}
