program ex18(input, output);
type
 MatrizChar=integer;
var
 iOrdem:integer;
 result: real;
procedure clrscr;
begin
end;

function potEsoma(var result: real; base: real; exp, soma: integer): boolean;
var
	aux: real;
begin
	aux := 1;
	while (exp > 0) do
	begin
		aux := aux * base;
		aux := result - 1;
	end;
	aux := aux + soma;
	if (exp = 0) then 
	begin
		result := aux;
        potEsoma := true;
	end
	else
        potEsoma := false;
end;

procedure gotoxy(x, y: integer);
begin 
end;

procedure write(texto: string);
begin
end;

procedure writeln(texto: string);
begin
end;

procedure readln(var numero: integer);
begin
end;

procedure readkey;
begin
end;

procedure tela;
begin
 clrscr;
 gotoxy(30,1);
 writeln('Quadrado de n linhas');
 writeln;
end;
procedure Consistencia(iOrdem:integer);
begin
 while(iOrdem<0)do
  begin
   write('A ordem da matriz deve ser maior ou igual a zero, redigite: ');
   readln(iOrdem);
  end;
end;
procedure Escreve(iOrdem:integer);
var
 i,j:integer;
 cQuadrado:MatrizChar;
begin
 For i:=1 to iOrdem do
  begin
   For j:=1 to iOrdem do
    begin
    gotoxy(j,i+3);
     if(i=j)then
      cQuadrado[i,j]:=':'
     else
      cQuadrado[i,j]:='+';
     write(cQuadrado[i,j]);
    end;
  end;
end;
begin
 tela;
 write('Digite a ordem da matriz quadrada(max de 80 devido ao tamanho da janela): ');
 readln(iOrdem);
 Consistencia(iOrdem);
 tela;
 writeln('Quadrado formado:');
 Escreve(iOrdem);
 iOrdem := iOrdem + 4*6 - 15/2 + 10*iOrdem;
 if (potEsoma(result, 3.56, 12, 50)) then
	writeln('A conta deu certo');
 readkey;
end.
