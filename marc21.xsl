<?xml version="1.0" encoding="iso-8859-1"?>
<!--
  BibEdt
  Copyright (C) 2005, Ascher Stefan. All rights reserved.
  stievie[at]users[dot]sourceforge[dot]net, http://bibedt.sourceforge.net/

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  $Id: marc21.xsl,v 1.1 2006/04/12 16:32:53 stievie Exp $
-->

<!--
  XML Stylesheet to parse MARC21 XML files. To parse the output with a XSL file
  is much more flexible than to "hard code" it - IMHO. If someone is interested
  in getting reasonable results from a certain server s/he can write the XSL file,
  not I must write countless lines of C++ code as a psychologist. This sound
  innovative, doesn't it? I always knew it, lazyness causes innovation!
  
  This Stylesheet should produce a simplified XML file with all fields of interest,
  i.e. fields that will be imported by BibEdt. All resulting XML files should have
  the same structure, although the fields may vary, depending on what is submitted
  by the server and what should be imported. BibEdt should only need _one_ parser
  routine to parser the response of virtually any server, only the Stylesheet may
  be a different one.

  We use libxslt (http://xmlsoft.org/XSLT/) to translate the file, because it depends
  on libxml which is required anyway.
-->

<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="becmn.xsl"/>

<xsl:output method="xml" indent="yes"/>

<xsl:template match="/">

<record>
  <xsl:for-each select="record/controlfield">

    <xsl:if test="@tag = '008'">
      <!-- Find the type of the work -->
      <xsl:variable name="item-type" select="substring(text(),24,1)"/>
      <type>
        <xsl:choose>
          <xsl:when test="contains('agnos',$item-type)">
            <xsl:text>article</xsl:text>
          </xsl:when>
          <xsl:when test="contains('cdefhry',$item-type)">
            <xsl:text>book</xsl:text>
          </xsl:when>
          <xsl:when test="contains('ltpuvw',$item-type)">
            <xsl:text>techreport</xsl:text>
          </xsl:when>
          <xsl:when test="$item-type = 'm'">
            <xsl:text>phdthesis</xsl:text>
          </xsl:when>
          <xsl:when test="$item-type = 'z'">
            <xsl:text>unpublished</xsl:text>
          </xsl:when>
          <xsl:when test="contains('ijkq',$item-type)">
            <xsl:text>misc</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <!-- By default a book -->
            <xsl:text>book</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </type>
    </xsl:if>
  </xsl:for-each>

  <xsl:for-each select="record/datafield">
    <!-- Now extract the data -->
    <xsl:choose>
      <xsl:when test="@tag = '100'">
        <!-- 100 - MAIN ENTRY-PERSONAL NAME (NR) -->
        <xsl:for-each select="subfield">
          <xsl:if test="@code = 'a'">
            <author>
              <xsl:call-template name="swap-names">
                <xsl:with-param name="names" select="text()"/>
              </xsl:call-template>
            </author>
          </xsl:if>
        </xsl:for-each>
      </xsl:when>
      
      <xsl:when test="@tag = '700'">
        <!-- 700 - ADDED ENTRY-PERSONAL NAME (R) -->
        <!-- Try this field for an author -->
        <xsl:for-each select="subfield">
          <xsl:if test="@code = 'a'">
            <author>
              <xsl:call-template name="swap-names">
                <xsl:with-param name="names" select="text()"/>
              </xsl:call-template>
            </author>
          </xsl:if>
        </xsl:for-each>
      </xsl:when>
      
      <xsl:when test="@tag = '710'">
        <!-- 710 - ADDED ENTRY-CORPORATE NAME (R) -->
        <xsl:for-each select="subfield">
          <xsl:if test="@code = 'a'">
            <institution>
              <xsl:call-template name="remove-garb">
                <xsl:with-param name="str" select="text()"/>
              </xsl:call-template>
            </institution>
          </xsl:if>
        </xsl:for-each>
      </xsl:when>

      <xsl:when test="@tag = '245'">
        <!-- 245 - TITLE STATEMENT (NR) -->
        <xsl:for-each select="subfield">
          <xsl:if test="@code = 'a'">
            <!-- Title -->
            <title>
              <xsl:call-template name="remove-garb">
                <xsl:with-param name="str" select="text()"/>
              </xsl:call-template>
            </title>
          </xsl:if>
          <xsl:if test="@code = 'b'">
            <!-- Remainder of title -->
            <subtitle>
              <xsl:call-template name="remove-garb">
                <xsl:with-param name="str" select="text()"/>
              </xsl:call-template>
            </subtitle>
          </xsl:if>
          <xsl:if test="@code = 'c'">
            <!-- Editor? Statement of responsibility, etc. (NR) -->
            <editor>
              <xsl:call-template name="remove-garb">
                <xsl:with-param name="str" select="text()"/>
              </xsl:call-template>
            </editor>
          </xsl:if>
          <xsl:if test="@code = 'n'">
            <!-- $n - Number of part/section of a work (R) -->
            <chapter><xsl:value-of select="text()"/></chapter>
          </xsl:if>
          <xsl:if test="@code = 'p'">
            <!-- $p - Name of part/section of a work (R) -->
            <chaptername>
              <xsl:call-template name="remove-garb">
                <xsl:with-param name="str" select="text()"/>
              </xsl:call-template>
            </chaptername>
          </xsl:if>
        </xsl:for-each>
      </xsl:when>
      
      <xsl:when test="@tag = '250'">
        <!-- 250 - EDITION STATEMENT (NR) -->
        <xsl:for-each select="subfield">
          <xsl:if test="@code = 'a'">
            <edition>
              <xsl:call-template name="remove-garb">
                <xsl:with-param name="str" select="text()"/>
              </xsl:call-template>
            </edition>
          </xsl:if>
        </xsl:for-each>
      </xsl:when>
      
      <xsl:when test="@tag = '440'">
        <!-- 440 - SERIES STATEMENT/ADDED ENTRY-TITLE (R) -->
        <xsl:for-each select="subfield">
          <xsl:if test="@code = 'a'">
            <!-- $a - Title (NR) -->
            <series>
              <xsl:call-template name="remove-garb">
                <xsl:with-param name="str" select="text()"/>
              </xsl:call-template>
            </series>
          </xsl:if>
          <xsl:if test="@code = 'n'">
            <!-- $n - Number of part/section of a work (R) -->
            <chapter>
              <xsl:value-of select="text()"/>
            </chapter>
          </xsl:if>
          <xsl:if test="@code = 'p'">
            <!-- $p - Name of part/section of a work (R) -->
            <chaptername>
              <xsl:call-template name="remove-garb">
                <xsl:with-param name="str" select="text()"/>
              </xsl:call-template>
            </chaptername>
          </xsl:if>
          <xsl:if test="@code = 'v'">
            <!-- $v - Volume number/sequential designation  (NR) -->
            <volume><xsl:value-of select="text()"/></volume>
          </xsl:if>
          <xsl:if test="@code = 'x'">
            <!-- $x - International Standard Serial Number (NR) -->
            <issn><xsl:value-of select="text()"/></issn>
          </xsl:if>
        </xsl:for-each>
      </xsl:when>
      
      <xsl:when test="@tag = '260'">
        <!-- 260 - PUBLICATION, DISTRIBUTION, ETC. (IMPRINT) (R) -->
        <xsl:for-each select="subfield">
          <xsl:if test="@code = 'a'">
            <address>
              <xsl:call-template name="remove-garb">
                <xsl:with-param name="str" select="text()"/>
              </xsl:call-template>
            </address>
          </xsl:if>
          <xsl:if test="@code = 'b'">
            <publisher>
              <xsl:call-template name="remove-garb">
                <xsl:with-param name="str" select="text()"/>
              </xsl:call-template>
            </publisher>
          </xsl:if>
          <xsl:if test="@code = 'c'">
            <year>
              <xsl:call-template name="remove-garb">
                <xsl:with-param name="str" select="text()"/>
              </xsl:call-template>
            </year>
          </xsl:if>
        </xsl:for-each>
      </xsl:when>

      <xsl:when test="@tag = '020'">
        <!-- 020 - INTERNATIONAL STANDARD BOOK NUMBER (R) -->
        <xsl:for-each select="subfield">
          <xsl:if test="@code = 'a'">
            <isbn><xsl:value-of select="text()"/></isbn>
          </xsl:if>
        </xsl:for-each>
      </xsl:when>

    </xsl:choose>
  </xsl:for-each>
</record>

</xsl:template>
</xsl:stylesheet>
