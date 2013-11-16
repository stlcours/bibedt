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

  $Id: xml2txt.xsl,v 1.5 2006/05/19 17:56:08 stievie Exp $
-->

<!--
  XML Stylesheets file for BibEdt XML export. This file should create a similar
  result than the BibTeX style plain.bst in plain text format.
-->

<!DOCTYPE xsl:stylesheet [
  <!ENTITY nbsp   " ">   <!-- nonbreaking space -->
  <!ENTITY emsp   " ">   <!-- normal space -->
  <!ENTITY thinsp " ">   <!-- spatium -->
  <!ENTITY ndash  "-">   <!-- N dash -->
  <!ENTITY mdash  "-">   <!-- M dash -->
  <!ENTITY rsquo  "'">   <!-- right single quote -->

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

<xsl:template match="/">

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
        <xsl:value-of select="title"/><xsl:text>. </xsl:text>
        <!-- Journal -->
        <xsl:if test="journal">
          <xsl:value-of select="journal"/><xsl:text>, </xsl:text>
        </xsl:if>
        <!-- Volume -->
        <xsl:if test="volume">
          <xsl:value-of select="volume"/>
          <xsl:if test="number">
            <xsl:text>(</xsl:text><xsl:value-of select="number"/><xsl:text>)</xsl:text>
            <xsl:if test="not(pages)">, </xsl:if>
          </xsl:if>
          <xsl:if test="pages">:</xsl:if>
        </xsl:if>
        <xsl:if test="not(volume)">
          <xsl:if test="number">
            <xsl:text>(</xsl:text><xsl:value-of select="number"/><xsl:text>)</xsl:text>
            <xsl:if test="pages">:</xsl:if>
            <xsl:if test="not(pages)">, </xsl:if>
          </xsl:if>
          <xsl:if test="not(number) and pages">pages </xsl:if>
        </xsl:if>
        <!-- Pages -->
        <xsl:if test="pages">
          <xsl:value-of select="pages"/><xsl:text>, </xsl:text>
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
        <xsl:value-of select="title"/>
        <!-- Volume -->
        <xsl:if test="volume">
          <xsl:text>, volume </xsl:text><xsl:value-of select="volume"/><xsl:text></xsl:text>
          <xsl:if test="series">
            <xsl:text> of </xsl:text>
          </xsl:if>
        </xsl:if>
        <!-- Series -->
        <xsl:if test="series">
          <xsl:value-of select="series"/>
        </xsl:if>
        <xsl:text>. </xsl:text>

        <!-- Publisher -->
        <xsl:if test="publisher">
          <xsl:value-of select="publisher"/><xsl:text>, </xsl:text>
        </xsl:if>
        <!-- Address -->
        <xsl:if test="address">
          <xsl:value-of select="address"/><xsl:text>, </xsl:text>
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
        <xsl:value-of select="title"/>
        <!-- Volume -->
        <xsl:if test="volume">
          <xsl:text>, volume </xsl:text><xsl:value-of select="volume"/>
        </xsl:if>
        <!-- Chapter -->
        <xsl:if test="chapter">
          <xsl:text>, chapter </xsl:text><xsl:value-of select="chapter"/>
        </xsl:if>
        <xsl:if test="pages">
          <xsl:text>, pages </xsl:text><xsl:value-of select="pages"/>
        </xsl:if>
        <xsl:text>. </xsl:text>
        <!-- Publisher -->
        <xsl:if test="publisher">
          <xsl:value-of select="publisher"/>
          <xsl:text>, </xsl:text>
        </xsl:if>
        <!-- Address -->
        <xsl:if test="address">
          <xsl:value-of select="address"/>
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
          <xsl:value-of select="organization"/><xsl:text>. </xsl:text>
        </xsl:if>

        <!-- Title -->
        <xsl:value-of select="title"/>
        <xsl:text>. </xsl:text>
        <!-- Organization -->
        <xsl:if test="organization">
          <xsl:value-of select="organization"/>
          <xsl:text>, </xsl:text>
        </xsl:if>
        <!-- Address -->
        <xsl:if test="address">
          <xsl:value-of select="address"/>
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
        <xsl:value-of select="title"/>
        <xsl:text>. </xsl:text>
        <xsl:text>Technical report</xsl:text>
        <xsl:if test="number">
          <xsl:text> </xsl:text><xsl:value-of select="number"/>
        </xsl:if>
        <xsl:text>. </xsl:text>
        <!-- Institution -->
        <xsl:if test="institution">
          <xsl:value-of select="institution"/><xsl:text>, </xsl:text>
        </xsl:if>
        <!-- Address -->
        <xsl:if test="address">
          <xsl:value-of select="address"/><xsl:text>, </xsl:text>
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
        <xsl:value-of select="title"/>
        <xsl:text>. </xsl:text>
        <xsl:text>PhD thesis</xsl:text>
        <xsl:if test="school">
          <xsl:text>, </xsl:text><xsl:value-of select="school"/>
        </xsl:if>
        <xsl:if test="address">
          <xsl:text>, </xsl:text><xsl:value-of select="address"/>
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
        <xsl:value-of select="title"/>
        <xsl:text>. </xsl:text>
        <xsl:text>Master's thesis</xsl:text>
        <xsl:if test="school">
          <xsl:text>, </xsl:text><xsl:value-of select="school"/>
        </xsl:if>
        <xsl:if test="address">
          <xsl:text>, </xsl:text><xsl:value-of select="address"/>
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
        <xsl:value-of select="title"/>
        <xsl:if test="address">
          <xsl:text>, </xsl:text><xsl:value-of select="address"/>
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
          <xsl:text>, </xsl:text><xsl:value-of select="booktitle"/>
        </xsl:if>
        <xsl:if test="pages">
          <xsl:text>, pages </xsl:text><xsl:value-of select="pages"/>
        </xsl:if>
        <xsl:if test="address">
          <xsl:text>, </xsl:text><xsl:value-of select="address"/>
        </xsl:if>
        <xsl:text>, </xsl:text>
        <xsl:if test="month">
          <xsl:value-of select="month"/><xsl:text> </xsl:text>
        </xsl:if>
        <xsl:value-of select="year"/>
        <xsl:if test="organization">
          <xsl:text>. </xsl:text><xsl:value-of select="organization"/>
        </xsl:if>
        <xsl:if test="publisher">
          <xsl:if test="organization">
            <xsl:text>, </xsl:text>
          </xsl:if>
          <xsl:if test="not(organization)">
            <xsl:text>. </xsl:text>
          </xsl:if>
          <xsl:value-of select="publisher"/>
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
        <xsl:value-of select="title"/>
        <xsl:text>. </xsl:text>
        <!-- How published -->
        <xsl:if test="howpublished">
          <xsl:value-of select="howpublished"/><xsl:text>, </xsl:text>
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
        <xsl:value-of select="title"/>
        <xsl:text>. </xsl:text>
        <!-- Note -->
        <xsl:if test="note">
          <xsl:value-of select="note"/><xsl:text>, </xsl:text>
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
         <xsl:value-of select="title"/> <xsl:text>. </xsl:text>
        <!-- Month -->
        <xsl:if test="month">
          <xsl:value-of select="month"/><xsl:text> </xsl:text>
        </xsl:if>
        <!-- Year -->
        <xsl:value-of select="year"/><xsl:text>.</xsl:text>
      </xsl:otherwise>
    </xsl:choose>

    <xsl:text>&#x0d;&#x0a;</xsl:text>
  </xsl:for-each>

</xsl:template>
</xsl:stylesheet>
