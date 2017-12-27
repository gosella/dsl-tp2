unit perceptron;

{$MODE OBJFPC}

interface

type
  TInput = array of Double;

  TPerceptron = class(TObject)
  public
    W: array of Double;
    b: Double;

    constructor Create(const Entradas: Integer);
    function Entradas: Integer;
    procedure Reiniciar;
    function Evaluar(const X: TInput): Integer;
    function Entrenar(const X: array of TInput;
                      const T: array of Integer;
                      const MaxPasos: Integer): Integer;
  end;

(*añado este comentario para molestar*)
implementation

constructor TPerceptron.Create(const Entradas: Integer);
begin
  SetLength(W, Entradas);
  Reiniciar;
end;

function TPerceptron.Entradas: Integer;
begin
  Result := Length(W);
end;

procedure TPerceptron.Reiniciar;
var
  i: Integer;
begin
  b := 0;
  for i := Low(W) to High(W) do
    W[i] := 0;
end;

function TPerceptron.Evaluar(const X: TInput): Integer;
var
  i: Integer;
  p: Double;
begin
  p := b;
  for i := Low(W) to High(W) do
    p := p + X[i] * W[i];

  if p > 0 then
    Evaluar := 1
  else
    Evaluar := 0;
end;

function TPerceptron.Entrenar(const X: array of TInput;
                              const T: array of Integer;
                              const MaxPasos: Integer): Integer;
var
  Entrenado: Boolean;
  i, j, n, d: Integer;
  y: Double;
begin
  Result := MaxPasos;

  for n := 1 to MaxPasos do begin
    Entrenado := True;

    for i := Low(X) to High(X) do begin
      y := Evaluar(X[i]);
      d := Trunc(T[i] - y);

      if d <> 0 then begin
        Entrenado := False;
        b := b + d;
        for j := Low(W) to High(W) do
          W[j] := W[j] + d * X[i][j];
      end;
    end;

    if Entrenado then begin
      Result := n;
      break;
    end;
  end;
end;

end.