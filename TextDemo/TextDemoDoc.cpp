
// TextDemoDoc.cpp : implementation of the CTextDemoDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TextDemo.h"
#endif

#include "TextDemoDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTextDemoDoc

IMPLEMENT_DYNCREATE(CTextDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CTextDemoDoc, CDocument)
	ON_COMMAND(ID_OPTIONS_FONT, &CTextDemoDoc::OnOptionsFont)
END_MESSAGE_MAP()


// CTextDemoDoc construction/destruction

CTextDemoDoc::CTextDemoDoc() noexcept
{
	// TODO: add one-time construction code here

}

CTextDemoDoc::~CTextDemoDoc()
{
}

BOOL CTextDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CTextDemoDoc serialization

void CTextDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CTextDemoDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CTextDemoDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CTextDemoDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CTextDemoDoc diagnostics

#ifdef _DEBUG
void CTextDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTextDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTextDemoDoc commands


void CTextDemoDoc::OnOptionsFont()
{
	
    // TODO: Add your command handler code here

    // display Font dialog box:           
    CFontDialog FontDialog;
    if (FontDialog.DoModal() != IDOK)
        return;

    // set m_Color:
    m_Color = FontDialog.GetColor();  // get color chosen by user

    // initialize font object:
    m_Font.DeleteObject();
    m_Font.CreateFontIndirect(&FontDialog.m_lf);

    // store values in m_LineTable:

    // store values chosen by user:
    int Num = 0;

    m_LineTable[Num++] = _T("Font Name: ") +
        FontDialog.GetFaceName();

    m_LineTable[Num] = "Font Size: ";
    char NumBuf[18];
    sprintf
    (NumBuf, "%d.%d points",
        FontDialog.GetSize() / 10,
        FontDialog.GetSize() % 10);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num++] = "";

    // store LOGFONT values:

    m_LineTable[Num++] = "LOGFONT fields:";

    m_LineTable[Num] = "lfHeight: ";
    sprintf(NumBuf, "%d", FontDialog.m_lf.lfHeight);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "lfWidth: ";
    sprintf(NumBuf, "%d", FontDialog.m_lf.lfWidth);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "lfEscapement: ";
    sprintf(NumBuf, "%d", FontDialog.m_lf.lfEscapement);
    m_LineTable[Num] += NumBuf;
    m_LineTable[Num++] += " (tenths of a degree)";

    m_LineTable[Num] = "lfOrientation: ";
    sprintf(NumBuf, "%d", FontDialog.m_lf.lfOrientation);
    m_LineTable[Num] += NumBuf;
    m_LineTable[Num++] += " (tenths of a degree)";

    m_LineTable[Num] = "lfWeight: ";
    sprintf(NumBuf, "%d", FontDialog.m_lf.lfWeight);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "lfItalic: ";
    sprintf(NumBuf, "%d", FontDialog.m_lf.lfItalic);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "lfUnderline: ";
    sprintf(NumBuf, "%d", FontDialog.m_lf.lfUnderline);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "lfStrikeOut: ";
    sprintf(NumBuf, "%d", FontDialog.m_lf.lfStrikeOut);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "lfCharSet: ";
    switch (FontDialog.m_lf.lfCharSet)
    {
    case ANSI_CHARSET:
        m_LineTable[Num++] += "ANSI_CHARSET";
        break;

    case OEM_CHARSET:
        m_LineTable[Num++] += "OEM_CHARSET";
        break;

    case SYMBOL_CHARSET:
        m_LineTable[Num++] += "SYMBOL_CHARSET";
        break;

    default:
        m_LineTable[Num++] += "unspecified character set";
        break;
    }

    m_LineTable[Num] = "lfOutPrecision: ";
    switch (FontDialog.m_lf.lfOutPrecision)
    {
    case OUT_CHARACTER_PRECIS:
        m_LineTable[Num++] += "OUT_CHARACTER_PRECIS";
        break;

    case OUT_DEFAULT_PRECIS:
        m_LineTable[Num++] += "OUT_DEFAULT_PRECIS";
        break;

    case OUT_STRING_PRECIS:
        m_LineTable[Num++] += "OUT_STRING_PRECIS";
        break;

    case OUT_STROKE_PRECIS:
        m_LineTable[Num++] += "OUT_STROKE_PRECIS";
        break;

    default:
        m_LineTable[Num++] += "unspecified output precision";
        break;
    }

    m_LineTable[Num] = "lfClipPrecision: ";
    switch (FontDialog.m_lf.lfClipPrecision)
    {
    case CLIP_CHARACTER_PRECIS:
        m_LineTable[Num++] += "CLIP_CHARACTER_PRECIS";
        break;

    case CLIP_DEFAULT_PRECIS:
        m_LineTable[Num++] += "CLIP_DEFAULT_PRECIS";
        break;

    case CLIP_STROKE_PRECIS:
        m_LineTable[Num++] += "CLIP_STROKE_PRECIS";
        break;

    default:
        m_LineTable[Num++] += "unspecified clipping precision";
        break;
    }

    m_LineTable[Num] = "lfQuality: ";
    switch (FontDialog.m_lf.lfQuality)
    {
    case DEFAULT_QUALITY:
        m_LineTable[Num++] += "DEFAULT_QUALITY";
        break;

    case DRAFT_QUALITY:
        m_LineTable[Num++] += "DRAFT_QUALITY";
        break;

    case PROOF_QUALITY:
        m_LineTable[Num++] += "PROOF_QUALITY";
        break;

    default:
        m_LineTable[Num++] += "unspecified output quality";
        break;
    }

    m_LineTable[Num] = "lfPitchAndFamily: ";
    switch (FontDialog.m_lf.lfPitchAndFamily & 0x0003)
    {
    case DEFAULT_PITCH:
        m_LineTable[Num] += "DEFAULT_PITCH; ";
        break;

    case FIXED_PITCH:
        m_LineTable[Num] += "FIXED_PITCH; ";
        break;

    case VARIABLE_PITCH:
        m_LineTable[Num] += "VARIABLE_PITCH; ";
        break;

    default:
        m_LineTable[Num] += "unspecified pitch; ";
        break;
    }
    switch (FontDialog.m_lf.lfPitchAndFamily & 0x00F0)
    {
    case FF_DECORATIVE:
        m_LineTable[Num++] += "FF_DECORATIVE";
        break;

    case FF_DONTCARE:
        m_LineTable[Num++] += "FF_DONTCARE";
        break;

    case FF_MODERN:
        m_LineTable[Num++] += "FF_MODERN";
        break;

    case FF_ROMAN:
        m_LineTable[Num++] += "FF_ROMAN";
        break;

    case FF_SCRIPT:
        m_LineTable[Num++] += "FF_SCRIPT";
        break;

    case FF_SWISS:
        m_LineTable[Num++] += "FF_SWISS";
        break;

    default:
        m_LineTable[Num++] += "unspecified family";
        break;
    }

    m_LineTable[Num] = "lfFaceName: ";
    m_LineTable[Num++] += FontDialog.m_lf.lfFaceName;

    m_LineTable[Num++] = "";

    // store TEXTMETRIC values:

    // create a device context object associated with the view window:
    POSITION Pos = GetFirstViewPosition();
    CView* PView = GetNextView(Pos);
    CClientDC ClientDC(PView);

    // select new font into device context object:        
    ClientDC.SelectObject(&m_Font);
    TEXTMETRIC TM;
    ClientDC.GetTextMetrics(&TM);

    m_LineTable[Num++] = "TEXTMETRIC fields:";

    m_LineTable[Num] = "tmHeight: ";
    sprintf(NumBuf, "%d", TM.tmHeight);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmAscent: ";
    sprintf(NumBuf, "%d", TM.tmAscent);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmDescent: ";
    sprintf(NumBuf, "%d", TM.tmDescent);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmInternalLeading: ";
    sprintf(NumBuf, "%d", TM.tmInternalLeading);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmExternalLeading: ";
    sprintf(NumBuf, "%d", TM.tmExternalLeading);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmAveCharWidth: ";
    sprintf(NumBuf, "%d", TM.tmAveCharWidth);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmMaxCharWidth: ";
    sprintf(NumBuf, "%d", TM.tmMaxCharWidth);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmWeight: ";
    sprintf(NumBuf, "%d", TM.tmWeight);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmOverhang: ";
    sprintf(NumBuf, "%d", TM.tmOverhang);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmDigitizedAspectX: ";
    sprintf(NumBuf, "%d", TM.tmDigitizedAspectX);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmDigitizedAspectY: ";
    sprintf(NumBuf, "%d", TM.tmDigitizedAspectY);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmFirstChar: ";
    sprintf(NumBuf, "%d", TM.tmFirstChar);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmLastChar: ";
    sprintf(NumBuf, "%d", TM.tmLastChar);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmDefaultChar: ";
    sprintf(NumBuf, "%d", TM.tmDefaultChar);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmBreakChar: ";
    sprintf(NumBuf, "%d", TM.tmBreakChar);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmItalic: ";
    sprintf(NumBuf, "%d", TM.tmItalic);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmUnderlined: ";
    sprintf(NumBuf, "%d", TM.tmUnderlined);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num] = "tmStruckOut: ";
    sprintf(NumBuf, "%d", TM.tmStruckOut);
    m_LineTable[Num++] += NumBuf;

    m_LineTable[Num++] = "tmPitchAndFamily: ";

    m_LineTable[Num] = "   Pitch Info: ";
    if (TM.tmPitchAndFamily & TMPF_FIXED_PITCH)
        m_LineTable[Num] += "variable pitch   ";
    else
        m_LineTable[Num] += "fixed pitch   ";
    if (TM.tmPitchAndFamily & TMPF_VECTOR)
        m_LineTable[Num] += "vector font   ";
    if (TM.tmPitchAndFamily & TMPF_TRUETYPE)
        m_LineTable[Num] += "TrueType font   ";
    if (TM.tmPitchAndFamily & TMPF_DEVICE)
        m_LineTable[Num] += "device font";
    Num++;

    m_LineTable[Num] = "   Family: ";
    switch (TM.tmPitchAndFamily & 0x00F0)
    {
    case FF_DECORATIVE:
        m_LineTable[Num++] += "FF_DECORATIVE";
        break;

    case FF_DONTCARE:
        m_LineTable[Num++] += "FF_DONTCARE";
        break;

    case FF_MODERN:
        m_LineTable[Num++] += "FF_MODERN";
        break;

    case FF_ROMAN:
        m_LineTable[Num++] += "FF_ROMAN";
        break;

    case FF_SCRIPT:
        m_LineTable[Num++] += "FF_SCRIPT";
        break;

    case FF_SWISS:
        m_LineTable[Num++] += "FF_SWISS";
        break;

    default:
        m_LineTable[Num++] += "unknown family";
        break;
    }

    m_LineTable[Num] = "tmCharSet: ";
    switch (TM.tmCharSet)
    {
    case ANSI_CHARSET:
        m_LineTable[Num++] += "ANSI_CHARSET";
        break;

    case OEM_CHARSET:
        m_LineTable[Num++] += "OEM_CHARSET";
        break;

    case SYMBOL_CHARSET:
        m_LineTable[Num++] += "SYMBOL_CHARSET";
        break;

    default:
        m_LineTable[Num++] += "unknown character set";
        break;
    }

    // force redrawing of view window:
    UpdateAllViews(NULL);
    
}
