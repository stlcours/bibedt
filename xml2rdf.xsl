<?xml version="1.0" encoding="UTF-8"?>
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

  $Id: xml2rdf.xsl,v 1.3 2005/10/26 20:43:16 stievie Exp $
-->

<!--
  XML Stylesheets file to convert XML files exported by BibEdt to RDF files with
  the Dublin Core notation as described in http://dublincore.org/documents/dcmes-xml/.
-->

<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="xml" indent="yes" />

<xsl:template name="format-names">
  <!-- Format names: Replace all ' and ' with ', ' except the last -->
  <xsl:param name="names"/>
  <xsl:variable name="raw-names" select="normalize-space($names)"/>
  <xsl:choose>
    <xsl:when test="contains($raw-names,' and ') and contains(substring-after($raw-names,' and '),' and ')">
      <xsl:value-of select="concat(substring-before($raw-names,' and '),', ')"/>
      <xsl:call-template name="format-names">
        <xsl:with-param name="names" select="substring-after($raw-names,' and ')"/>
      </xsl:call-template>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="$raw-names"/>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<xsl:template match="/">

<rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
    xmlns:dc="http://purl.org/dc/elements/1.1/">

  <xsl:for-each select="bibliography/bibitem">
    <rdf:Description>
      <xsl:if test="title">
        <dc:title><xsl:value-of select="title"/></dc:title>
      </xsl:if>
      <xsl:if test="author">
        <dc:creator>
          <xsl:call-template name="format-names">
            <xsl:with-param name="names" select="author"/>
          </xsl:call-template>
        </dc:creator>
      </xsl:if>
      <xsl:if test="abstract">
        <dc:description><xsl:value-of select="abstract"/></dc:description>
      </xsl:if>
      <xsl:if test="publisher">
        <dc:publisher><xsl:value-of select="publisher"/></dc:publisher>
      </xsl:if>
      <xsl:if test="year">
        <dc:date><xsl:value-of select="year"/></dc:date>
      </xsl:if>
      <dc:type><xsl:value-of select="type"/></dc:type>
      <xsl:if test="doi">
        <dc:identifier><xsl:value-of select="doi"/></dc:identifier>
      </xsl:if>
      <xsl:if test="not(doi)">
        <xsl:if test="url">
          <dc:identifier><xsl:value-of select="url"/></dc:identifier>
        </xsl:if>
        <xsl:if test="not(url)">
          <xsl:if test="isbn">
            <dc:identifier><xsl:value-of select="isbn"/></dc:identifier>
          </xsl:if>
        </xsl:if>
      </xsl:if>
    </rdf:Description>
  </xsl:for-each>

</rdf:RDF>
</xsl:template>
</xsl:stylesheet>
