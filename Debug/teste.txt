program ex18(input, output);
type
 MatrizChar=array[1..80,1..80]of char;
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
var
 iOrdem:integer;
begin
 tela;
 write('Digite a ordem da matriz quadrada(max de 80 devido ao tamanho da janela): ');
 readln(iOrdem);
 Consistencia(iOrdem);
 tela;
 writeln('Quadrado formado:');
 Escreve(iOrdem);
 readkey;
end.
