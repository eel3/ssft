{
  -*- coding: utf-8-unix -*-
  vim:fileencoding=utf-8:ff=unix

  FIXME: <edit a description of this file>
}

{$CODEPAGE UTF8}
{$MODE OBJFPC}
{$LONGSTRINGS ON}

program ProgName;   // FIXME

uses
  CustApp,
  SysUtils;

type
  TMyApp = class(TCustomApplication)
  protected
    procedure DoRun; override;
  end;

procedure TMyApp.DoRun;
var
  i : Integer;      // FIXME
begin
  // FIXME: write a code here.
  WriteLn(Title);
  for i := 1 to ParamCount do
    WriteLn(Params[i]);
  Terminate;
end;

var
  app : TMyApp;

begin
  app := TMyApp.Create(nil);
  app.Title := ExtractFileName(app.ExeName);
  app.Run;
  app.Destroy;
end.
