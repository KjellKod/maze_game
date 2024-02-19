#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include "pugixml.hpp"

namespace dummy_for_verifying_pugixml {
  // from: https://code.google.com/p/pugixml/source/browse/trunk/docs/samples/xgconsole.xml?r=764

std::string raw{"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"\
                          "    <Profile FormatVersion=\"1\">"\
                          "        <Tools>"\
                          "            <Tool Filename=\"jam\" AllowIntercept=\"true\">"\
                    "<Description>Jamplus build system</Description>"\
            "</Tool>"\
            "<Tool Filename=\"mayabatch.exe\" AllowRemote=\"true\" OutputFileMasks=\"*.dae\" DeriveCaptionFrom=\"lastparam\" Timeout=\"40\" />"\
            "<Tool Filename=\"meshbuilder_*.exe\" AllowRemote=\"false\" OutputFileMasks=\"*.mesh\" DeriveCaptionFrom=\"lastparam\" Timeout=\"10\" />"\
            "<Tool Filename=\"texbuilder_*.exe\" AllowRemote=\"true\" OutputFileMasks=\"*.tex\" DeriveCaptionFrom=\"lastparam\" />"\
            "<Tool Filename=\"shaderbuilder_*.exe\" AllowRemote=\"true\" DeriveCaptionFrom=\"lastparam\" />"\
        "</Tools>"\
    "</Profile>"};
}


TEST(FigureOut_XML, PrintOut_pugixml_example)
{
  using namespace std;
  using namespace dummy_for_verifying_pugixml;
  pugi::xml_document doc;
  auto result = doc.load_string(raw.c_str());
  ASSERT_TRUE(result.status == pugi::status_ok) << result.description();
  pugi::xml_node tools = doc.child("Profile").child("Tools");
  for (pugi::xml_node tool = tools.first_child(); tool; tool = tool.next_sibling())
  {
    cout << "Tool:";

    for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())
      cout << " " << attr.name() << "=" << attr.value();

    cout << std::endl;
  }
}
