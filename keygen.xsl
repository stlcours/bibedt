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

  $Id: keygen.xsl,v 1.5 2006/08/13 15:50:03 stievie Exp $
-->

<!--
  XML Stylesheet to generate BibTeX keys. The XML file to be transformed is the
  same as it is exported with the XML exporter.
  This file generates a key in the form of author1[+author2[+...]]:year.
  
  First this style sheet is used to generate a key, then BibEdt removes all characters
  that shopuldn't be used for keys and then it makes the key unique, if it isn't,
  with appending a-z.
-->

<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="becmn.xsl"/>

<xsl:output method="text" encoding="ISO-8859-1"/>

<xsl:template name="gen-key">
  <!-- Generate the key from authors -->
  <xsl:param name="val"/>
  <xsl:variable name="strLen" select="string-length($val)" />
  <xsl:variable name="strLastChar" select="substring($val, $strLen, 1)" />
  <xsl:choose>
    <xsl:when test="starts-with($val, '{') and ($strLastChar = '}')">
      <xsl:variable name="res" select="substring($val, 1, $strLen - 1)"/>
      <!-- Remove spaces -->
      <xsl:value-of select="translate($res, ' ', '')"/>
    </xsl:when>
    <xsl:otherwise>
      <xsl:choose>
        <xsl:when test="contains($val, ' ')">
        <xsl:variable name="auth">
          <xsl:choose>
            <xsl:when test="contains($val, ' and ')">
              <!-- Extract name before the first ' and ' -->
              <xsl:value-of select="substring-before($val, ' and ')"/>
            </xsl:when>
            <xsl:otherwise>
              <xsl:value-of select="$val"/>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:variable>
        <xsl:variable name="res">
          <!-- Extract last name, the part before the last ' ' -->
          <xsl:call-template name="substring-after-last">
            <xsl:with-param name="text" select="$auth"/>
            <xsl:with-param name="chars" select="' '"/>
          </xsl:call-template>
        </xsl:variable>
        <xsl:call-template name="to-lower">
          <!-- Make it lower case -->
          <xsl:with-param name="text" select="$res"/>
        </xsl:call-template>
        <xsl:if test="contains(substring-after($val, ' and '), ' ')">
          <!-- If there are other authors appen a + -->
          <xsl:text>+</xsl:text>
        </xsl:if>
          <xsl:call-template name="gen-key">
            <!-- Call it as long as there are other authors -->
            <xsl:with-param name="val" select="substring-after($val, ' and ')"/>
          </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>
          <!-- There is no space, just return the value -->
          <xsl:call-template name="to-lower">
            <xsl:with-param name="text" select="$val"/>
          </xsl:call-template>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<xsl:template match="bibliography/bibitem">
  <!-- See what can be used to generate the key -->
  <xsl:choose>
    <xsl:when test="author">
      <xsl:call-template name="gen-key">
        <xsl:with-param name="val" select="author"/>
      </xsl:call-template>
    </xsl:when>
    <xsl:when test="editor">
      <xsl:call-template name="gen-key">
        <xsl:with-param name="val" select="editor"/>
      </xsl:call-template>
    </xsl:when>
    <xsl:when test="organization">
      <xsl:call-template name="gen-key">
        <xsl:with-param name="val" select="organization"/>
      </xsl:call-template>
    </xsl:when>
  </xsl:choose>

  <!-- Append the year -->
  <xsl:if test="year">
    <xsl:text>:</xsl:text><xsl:value-of select="year"/>
  </xsl:if>
</xsl:template>

</xsl:stylesheet>
