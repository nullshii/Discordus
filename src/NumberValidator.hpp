#pragma once

#include <wx/wx.h>

namespace NumberValidator {
inline wxTextValidator Validator(wxFILTER_INCLUDE_CHAR_LIST);
inline void Init() {
  wxArrayString list;
  wxString valid_chars(wxT("0123456789"));
  size_t len = valid_chars.Length();
  for (size_t i = 0; i < len; i++)
    list.Add(wxString(valid_chars.GetChar(i)));
  Validator.SetIncludes(list);
}
} // namespace NumberValidator