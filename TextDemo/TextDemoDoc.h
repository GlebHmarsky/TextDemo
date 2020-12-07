
// TextDemoDoc.h : interface of the CTextDemoDoc class
//


#pragma once
const int NUMLINES = 42;	// количество строк, сохраненных
						// в документе и отображенных
						// в окне представления

class CTextDemoDoc : public CDocument
{
public:
	COLORREF m_Color;
	CString m_LineTable[NUMLINES];
	CFont m_Font;
protected: // create from serialization only
	CTextDemoDoc() noexcept;
	DECLARE_DYNCREATE(CTextDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CTextDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnOptionsFont();
};
