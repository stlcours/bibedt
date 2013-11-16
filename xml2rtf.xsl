<?xml version="1.0" encoding="ISO-8859-1"?>
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

  $Id: xml2rtf.xsl,v 1.5 2006/05/19 17:56:08 stievie Exp $
-->

<!--
  XML Stylesheets file for BibEdt XML export. This file should create a similar
  result than the BibTeX style plain.bst in RTF format.
-->

<!DOCTYPE xsl:stylesheet [
  <!ENTITY nbsp   "&#x000A0;">   <!-- nonbreaking space -->
  <!ENTITY emsp   "&#x02003;">   <!-- normal space -->
  <!ENTITY thinsp "&#x02009;">   <!-- spatium -->
  <!ENTITY ndash  "&#x02013;">   <!-- N dash -->
  <!ENTITY mdash  "&#x02014;">   <!-- M dash -->
  <!ENTITY rsquo  "&#x02019;">   <!-- right single quote -->

  <!-- Localization, modify to translate to your language -->
  <!ENTITY title      "Bibliography">
  <!ENTITY pages      "pages">
  <!ENTITY volume     "volume">
  <!ENTITY of         "of">
  <!ENTITY edition    "edition">
  <!ENTITY chapter    "chapter">
  <!ENTITY phdthesis  "PhD thesis">
  <!ENTITY techreport "Technical report">
  <!ENTITY mstthesis  "Master&rsquo;s thesis">
  <!ENTITY editors    "editors">
  <!ENTITY in         "In">
]>

<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="becmn.xsl"/>

<xsl:output method="text" encoding="ISO-8859-1"/>

<xsl:template name="encode-rtf">
  <!-- Replace special Characters with RTF characters -->
  <xsl:param name="str"/>
  <xsl:variable name="res">
    <xsl:call-template name="str-replace">
      <xsl:with-param name="str" select="$str"/>
      <xsl:with-param name="old" select="'&nbsp;'"/>
      <xsl:with-param name="new" select="' '"/>
    </xsl:call-template>
  </xsl:variable>
  <xsl:variable name="res1">
    <xsl:call-template name="str-replace">
      <xsl:with-param name="str" select="$res"/>
      <xsl:with-param name="old" select="'&thinsp;'"/>
      <xsl:with-param name="new" select="' '"/>
    </xsl:call-template>
  </xsl:variable>
  <xsl:variable name="res2">
    <xsl:call-template name="str-replace">
      <xsl:with-param name="str" select="$res1"/>
      <xsl:with-param name="old" select="'&mdash;'"/>
      <xsl:with-param name="new" select="'\emdash '"/>
    </xsl:call-template>
  </xsl:variable>
  <xsl:variable name="res3">
    <xsl:call-template name="str-replace">
      <xsl:with-param name="str" select="$res2"/>
      <xsl:with-param name="old" select="'&ndash;'"/>
      <xsl:with-param name="new" select="'\endash '"/>
    </xsl:call-template>
  </xsl:variable>
  <xsl:variable name="res4">
    <xsl:call-template name="str-replace">
      <xsl:with-param name="str" select="$res3"/>
      <xsl:with-param name="old" select="'&rsquo;'"/>
      <xsl:with-param name="new" select="'\rquote '"/>
    </xsl:call-template>
  </xsl:variable>
  <xsl:value-of select="$res4"/>
</xsl:template>

<xsl:template match="/">

<xsl:text>{\rtf1\ansi\deff0\deftab720{\fonttbl{\f0\fmodern Times New Roman;}}
{\colortbl\red0\green0\blue0;\red0\green0\blue255;\red0\green130\blue0;}
{\info{\comment Generated by BibEdt with xml2rtf.xsl}
{\title Bibliography}}
\deflang1033\pard\plain\f0\fs24 </xsl:text>

  <xsl:for-each select="bibliography/bibitem">

    <xsl:variable name="item-type" select="type"/>
      <!-- The type is always exported in lower case letters. -->

      <xsl:choose>

        <!--========================= Article ===========================-->
        <xsl:when test="$item-type = 'article'">
          <!-- The Author -->
          <xsl:call-template name="format-names">
            <xsl:with-param name="names" select="author"/>
          </xsl:call-template>
          <xsl:text>. </xsl:text>
          <!-- Title -->
          <a href="{url}">
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="title"/>
            </xsl:call-template>
          </a><xsl:text>. </xsl:text>
          <!-- Journal -->
          <xsl:if test="journal">
            <xsl:text>{\i </xsl:text>
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="journal"/>
            </xsl:call-template>
            <xsl:text>}, </xsl:text>
          </xsl:if>
          <!-- Volume -->
          <xsl:if test="volume">
            <xsl:value-of select="volume"/>
            <xsl:if test="number">
              <xsl:text>(</xsl:text><xsl:value-of select="number"/><xsl:text>)</xsl:text>
              <xsl:if test="not(pages)"><xsl:text>, </xsl:text></xsl:if>
            </xsl:if>
            <xsl:if test="pages">:</xsl:if>
          </xsl:if>
          <xsl:if test="not(volume)">
            <xsl:if test="number">
              <xsl:text>(</xsl:text><xsl:value-of select="number"/><xsl:text>)</xsl:text>
              <xsl:if test="pages">:</xsl:if>
              <xsl:if test="not(pages)"><xsl:text>, </xsl:text></xsl:if>
            </xsl:if>
            <xsl:if test="not(number) and pages"><xsl:text>pages </xsl:text></xsl:if>
          </xsl:if>
          <!-- Pages -->
          <xsl:if test="pages">
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="pages"/>
            </xsl:call-template>
            <xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Month -->
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text> </xsl:text>
          </xsl:if>
          <!-- Year -->
          <xsl:value-of select="year"/><xsl:text>.</xsl:text>
        </xsl:when>

        <!--========================== Book =============================-->
        <xsl:when test="$item-type = 'book'">
          <!-- The Author -->
          <xsl:if test="author">
            <xsl:call-template name="format-names">
              <xsl:with-param name="names" select="author"/>
            </xsl:call-template>
            <xsl:text>. </xsl:text>
          </xsl:if>
          <xsl:if test="not(author)">
            <xsl:if test="editor">
              <xsl:call-template name="format-names">
                <xsl:with-param name="names" select="editor"/>
              </xsl:call-template>
              <xsl:text>. </xsl:text>
            </xsl:if>
          </xsl:if>
          <!-- Title -->
          <xsl:text>{\i </xsl:text>
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="title"/>
            </xsl:call-template>
          <xsl:text>}</xsl:text>
          <!-- Volume -->
          <xsl:if test="volume">
            <xsl:text>, volume </xsl:text><xsl:value-of select="volume"/>
            <xsl:if test="series">
              <xsl:text> of </xsl:text>
            </xsl:if>
          </xsl:if>
          <!-- Series -->
          <xsl:if test="series">
            <xsl:text>{\i </xsl:text>
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="series"/>
            </xsl:call-template>
            <xsl:text>}</xsl:text>
          </xsl:if>
          <xsl:text>. </xsl:text>

          <!-- Publisher -->
          <xsl:if test="publisher">
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="publisher"/>
            </xsl:call-template>
            <xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Address -->
          <xsl:if test="address">
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="address"/>
            </xsl:call-template>
            <xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Edition -->
          <xsl:if test="edition">
            <xsl:value-of select="edition"/><xsl:text> edition. </xsl:text>
          </xsl:if>
          <!-- Month -->
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text> </xsl:text>
          </xsl:if>
          <!-- Year -->
          <xsl:value-of select="year"/><xsl:text>.</xsl:text>
        </xsl:when>

        <!--========================= InBook ============================-->
        <xsl:when test="$item-type = 'inbook'">
          <!-- The Author -->
          <xsl:call-template name="format-names">
            <xsl:with-param name="names" select="author"/>
          </xsl:call-template>
          <xsl:text>. </xsl:text>
          <!-- Title -->
          <xsl:text>{\i </xsl:text>
          <xsl:call-template name="encode-rtf">
            <xsl:with-param name="str" select="title"/>
          </xsl:call-template>
          <xsl:text>}</xsl:text>
          <!-- Volume -->
          <xsl:if test="volume">
            <xsl:text>, volume </xsl:text><xsl:value-of select="volume"/>
          </xsl:if>
          <!-- Chapter -->
          <xsl:if test="chapter">
            <xsl:text>, chapter </xsl:text><xsl:value-of select="chapter"/>
          </xsl:if>
          <xsl:if test="pages">
            <xsl:text>, pages </xsl:text>
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="pages"/>
            </xsl:call-template>
          </xsl:if>
          <xsl:text>. </xsl:text>
          <!-- Publisher -->
          <xsl:if test="publisher">
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="publisher"/>
            </xsl:call-template>
            <xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Address -->
          <xsl:if test="address">
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="address"/>
            </xsl:call-template>
            <xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Edition -->
          <xsl:if test="edition">
            <xsl:value-of select="edition"/><xsl:text> edition. </xsl:text>
          </xsl:if>
          <!-- Month -->
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text> </xsl:text>
          </xsl:if>
          <!-- Year -->
          <xsl:value-of select="year"/><xsl:text>.</xsl:text>
        </xsl:when>

        <!--========================= Manual ============================-->
        <xsl:when test="$item-type = 'manual'">
          <!-- The Author -->
          <xsl:if test="author">
            <xsl:call-template name="format-names">
              <xsl:with-param name="names" select="author"/>
            </xsl:call-template>
            <xsl:text>. </xsl:text>
          </xsl:if>
          <xsl:if test="not(author) and organization">
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="organization"/>
            </xsl:call-template>
            <xsl:text>. </xsl:text>
          </xsl:if>

          <!-- Title -->
          <xsl:text>{\i </xsl:text>
          <xsl:call-template name="encode-rtf">
            <xsl:with-param name="str" select="title"/>
          </xsl:call-template>
          <xsl:text>}</xsl:text>
          <xsl:text>. </xsl:text>
          <!-- Organization -->
          <xsl:if test="organization">
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="organization"/>
            </xsl:call-template>
            <xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Address -->
          <xsl:if test="address">
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="address"/>
            </xsl:call-template>
            <xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Month -->
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:if test="year"><xsl:text> </xsl:text></xsl:if>
          </xsl:if>
          <!-- Year -->
          <xsl:if test="year">
            <xsl:value-of select="year"/>
          </xsl:if>
          <xsl:text>.</xsl:text>
        </xsl:when>

        <!--==================== Technical report =======================-->
        <xsl:when test="$item-type = 'techreport'">
          <!-- The Author -->
          <xsl:call-template name="format-names">
            <xsl:with-param name="names" select="author"/>
          </xsl:call-template>
          <xsl:text>. </xsl:text>
          <!-- Title -->
          <xsl:call-template name="encode-rtf">
            <xsl:with-param name="str" select="title"/>
          </xsl:call-template>
          <xsl:text>. </xsl:text>
          <xsl:text>Technical report</xsl:text>
          <xsl:if test="number">
            <xsl:text> </xsl:text><xsl:value-of select="number"/>
          </xsl:if>
          <xsl:text>. </xsl:text>
          <!-- Institution -->
          <xsl:if test="institution">
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="institution"/>
            </xsl:call-template>
            <xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Address -->
          <xsl:if test="address">
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="address"/>
            </xsl:call-template>
            <xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Month -->
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text> </xsl:text>
          </xsl:if>
          <!-- Year -->
          <xsl:value-of select="year"/><xsl:text>.</xsl:text>
        </xsl:when>

        <!--======================== PhD Thesis =========================-->
        <xsl:when test="$item-type = 'phdthesis'">
          <!-- The Author -->
          <xsl:call-template name="format-names">
            <xsl:with-param name="names" select="author"/>
          </xsl:call-template>
          <xsl:text>. </xsl:text>
          <!-- Title -->
          <xsl:text>{\i </xsl:text>
          <xsl:call-template name="encode-rtf">
            <xsl:with-param name="str" select="title"/>
          </xsl:call-template>
          <xsl:text>}</xsl:text>
          <xsl:text>. </xsl:text>
          <xsl:text>PhD thesis</xsl:text>
          <xsl:if test="school">
            <xsl:text>, </xsl:text>
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="school"/>
            </xsl:call-template>
          </xsl:if>
          <xsl:if test="address">
            <xsl:text>, </xsl:text>
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="address"/>
            </xsl:call-template>
          </xsl:if>
          <xsl:text>, </xsl:text>
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text> </xsl:text>
          </xsl:if>
          <xsl:value-of select="year"/><xsl:text>.</xsl:text>
        </xsl:when>

        <!--====================== Master Thesis ========================-->
        <xsl:when test="$item-type = 'mastersthesis'">
          <!-- The Author -->
          <xsl:call-template name="format-names">
            <xsl:with-param name="names" select="author"/>
          </xsl:call-template>
          <xsl:text>. </xsl:text>
          <!-- Title -->
          <xsl:call-template name="encode-rtf">
            <xsl:with-param name="str" select="title"/>
          </xsl:call-template>
          <xsl:text>. </xsl:text>
          <xsl:text>Master's thesis</xsl:text>
          <xsl:if test="school">
            <xsl:text>, </xsl:text>
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="school"/>
            </xsl:call-template>
          </xsl:if>
          <xsl:if test="address">
            <xsl:text>, </xsl:text>
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="address"/>
            </xsl:call-template>
          </xsl:if>
          <xsl:text>, </xsl:text>
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text> </xsl:text>
          </xsl:if>
          <xsl:value-of select="year"/><xsl:text>.</xsl:text>
        </xsl:when>

        <!--======================== Proceedings ========================-->
        <xsl:when test="$item-type = 'proceedings'">
          <!-- Editor -->
          <xsl:if test="editor">
            <xsl:call-template name="format-names">
              <xsl:with-param name="names" select="editor"/>
            </xsl:call-template>
            <xsl:text>, editors. </xsl:text>
          </xsl:if>
          <xsl:text>{\i </xsl:text>
          <xsl:call-template name="encode-rtf">
            <xsl:with-param name="str" select="title"/>
          </xsl:call-template>
          <xsl:text>}</xsl:text>
          <xsl:if test="address">
            <xsl:text>, </xsl:text>
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="address"/>
            </xsl:call-template>
          </xsl:if>
          <xsl:text>, </xsl:text>
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text> </xsl:text>
          </xsl:if>
          <xsl:value-of select="year"/><xsl:text>.</xsl:text>
        </xsl:when>

        <!--====================== In Proceedings =======================-->
        <xsl:when test="$item-type = 'inproceedings'">
          <!-- Editor -->
          <xsl:if test="author">
            <xsl:call-template name="format-names">
              <xsl:with-param name="names" select="author"/>
            </xsl:call-template>
            <xsl:text>. </xsl:text>
          </xsl:if>
          <xsl:value-of select="title"/>
          <xsl:if test="editor">
            <xsl:text> In </xsl:text>
            <xsl:call-template name="format-names">
              <xsl:with-param name="names" select="editor"/>
            </xsl:call-template>
            <xsl:text>, editors</xsl:text>
          </xsl:if>
          <xsl:if test="booktitle">
            <xsl:text>, </xsl:text><xsl:text>{\i </xsl:text>
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="booktitle"/>
            </xsl:call-template>
            <xsl:text>}</xsl:text>
          </xsl:if>
          <xsl:if test="pages">
            <xsl:text>, pages </xsl:text>
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="pages"/>
            </xsl:call-template>
          </xsl:if>
          <xsl:if test="address">
            <xsl:text>, </xsl:text>
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="address"/>
            </xsl:call-template>
          </xsl:if>
          <xsl:text>, </xsl:text>
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text> </xsl:text>
          </xsl:if>
          <xsl:value-of select="year"/>
          <xsl:if test="organization">
            <xsl:text>. </xsl:text>
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="organization"/>
            </xsl:call-template>
          </xsl:if>
          <xsl:if test="publisher">
            <xsl:if test="organization">
              <xsl:text>, </xsl:text>
            </xsl:if>
            <xsl:if test="not(organization)">
              <xsl:text>. </xsl:text>
            </xsl:if>
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="publisher"/>
            </xsl:call-template>
          </xsl:if>
          <xsl:text>.</xsl:text>
        </xsl:when>

        <!--=========================== Misc ============================-->
        <xsl:when test="$item-type = 'misc'">
          <!-- The Author -->
          <xsl:call-template name="format-names">
            <xsl:with-param name="names" select="author"/>
          </xsl:call-template>
          <xsl:text>. </xsl:text>
          <!-- Title -->
          <xsl:call-template name="encode-rtf">
            <xsl:with-param name="str" select="title"/>
          </xsl:call-template>
          <xsl:text>. </xsl:text>
          <!-- How published -->
          <xsl:if test="howpublished">
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="howpublished"/>
            </xsl:call-template>
            <xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Month -->
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text> </xsl:text>
          </xsl:if>
          <!-- Year -->
          <xsl:value-of select="year"/><xsl:text>.</xsl:text>
        </xsl:when>

        <!--======================= Unpublished =========================-->
        <xsl:when test="$item-type = 'unpublished'">
          <!-- The Author -->
          <xsl:call-template name="format-names">
            <xsl:with-param name="names" select="author"/>
          </xsl:call-template>
          <xsl:text>. </xsl:text>
          <!-- Title -->
          <xsl:call-template name="encode-rtf">
            <xsl:with-param name="str" select="title"/>
          </xsl:call-template>
          <xsl:text>. </xsl:text>
          <!-- Note -->
          <xsl:if test="note">
            <xsl:call-template name="encode-rtf">
              <xsl:with-param name="str" select="note"/>
            </xsl:call-template>
            <xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Month -->
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text> </xsl:text>
          </xsl:if>
          <!-- Year -->
          <xsl:value-of select="year"/><xsl:text>.</xsl:text>
        </xsl:when>

        <!--========================= Unknown ===========================-->
        <xsl:otherwise>
          <xsl:message>Unknown type of <xsl:value-of select="key"/> &#x22;<xsl:value-of select="$item-type"/>&#x22;</xsl:message>
          <!-- The Author -->
          <xsl:call-template name="format-names">
            <xsl:with-param name="names" select="author"/>
          </xsl:call-template>
          <xsl:text>. </xsl:text>
          <!-- Title -->
          <xsl:text>{\i </xsl:text>
          <xsl:call-template name="encode-rtf">
            <xsl:with-param name="str" select="title"/>
          </xsl:call-template>
          <xsl:text>}</xsl:text><xsl:text>. </xsl:text>
          <!-- Month -->
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text> </xsl:text>
          </xsl:if>
          <!-- Year -->
          <xsl:value-of select="year"/><xsl:text>.</xsl:text>
        </xsl:otherwise>
      </xsl:choose>

    <xsl:text>&#x0d;&#x0a;\par </xsl:text>
  </xsl:for-each>


<xsl:text>
}
</xsl:text>

</xsl:template>
</xsl:stylesheet>
