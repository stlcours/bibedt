<?xml version="1.0" encoding="ISO-8859-1"?>
<!--
  BibEdt
  Copyright (C) 2006, Ascher Stefan. All rights reserved.
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

  $Id: preview.xsl,v 1.21 2006/08/13 15:50:03 stievie Exp $
-->

<!--
  XML Stylesheets file for the preview pane. This file is similar to plain.xsl
  but produces simpler HTML, i.e. with no CSS, since the internal HTML viewer
  does not support advanced HTML techniques.
-->

<!DOCTYPE xsl:stylesheet [
  <!ENTITY nbsp   "&#x00020;">   <!-- nonbreaking space -->
  <!ENTITY emsp   "&#x02003;">   <!-- normal space -->
  <!ENTITY thinsp "&#x02009;">   <!-- spatium -->
  <!ENTITY ndash  "&#x02013;">   <!-- N dash -->
  <!ENTITY mdash  "&#x02014;">   <!-- M dash -->
  <!ENTITY lsquo  "&#x02018;">   <!-- left single quote -->
  <!ENTITY rsquo  "&#x02019;">   <!-- right single quote -->
  <!ENTITY ldquo  "&#x0201C;">   <!--left double quotes -->
  <!ENTITY rdquo  "&#x0201D;">   <!--right double quotes -->
  <!ENTITY bdquo  "&#x0201E;">   <!--bottom double quotes -->
  <!ENTITY laquo  "&#x000AB;">   <!--left angle quotes (guillemets) -->
  <!ENTITY raquo  "&#x000BB;">   <!--right angle quotes (guillemets) -->

  <!-- Localization, modify to translate to your language -->
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

  <!ENTITY abstract   "Abstract">
  <!ENTITY keywords   "Keywords">
]>

<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="becmn.xsl"/>

<xsl:output method="html" encoding="UTF-8"/>

<xsl:template name="valid-attri">
  <!-- Make an attribute valid, in this case just replace + with - -->
  <xsl:param name="val"/>
  <xsl:value-of select="translate($val,'+','-')"/>
</xsl:template>

<xsl:template name="make-link">
  <!-- Split links separated with ; -->
  <xsl:param name="val"/>
  <xsl:choose>
    <xsl:when test="contains($val, ';')">
      <xsl:variable name="ref" select="substring-before($val,';')"/>
      <li><font family="monospace" size="-1"><a href="{$ref}"><xsl:value-of select="$ref"/></a></font></li>
      <xsl:call-template name="make-link">
        <xsl:with-param name="val" select="substring-after($val,';')"/>
      </xsl:call-template>
    </xsl:when>
    <xsl:otherwise>
      <li><font family="monospace" size="-1"><a href="{$val}"><xsl:value-of select="$val"/></a></font></li>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<xsl:template name="make-doi">
  <!-- Prefix doi: if not present -->
  <xsl:param name="val"/>
  <xsl:choose>
    <xsl:when test="not(contains($val, 'doi:'))">
      <xsl:variable name="ref" select="concat('doi:', $val)"/>
      <a href="{$ref}"><xsl:value-of select="$ref"/></a>
    </xsl:when>
    <xsl:otherwise>
      <a href="{$val}"><xsl:value-of select="$val"/></a>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<xsl:template name="pconv-url">
  <!-- Make a real URL -->
  <xsl:param name="str" select="''"/>
  <xsl:choose>
    <xsl:when test="contains($str,'\url{')">
      <xsl:value-of select="substring-before($str,'\url{')"/>
      <xsl:variable name="url" select="substring-before(substring-after($str,'\url{'),'}')"/>
      <font family="monospace"><a href="{$url}"><xsl:value-of select="$url"/></a></font>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="$str"/>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<xsl:template match="/">
<html><body>

  <xsl:for-each select="bibliography/bibitem">
    <p>
      <xsl:attribute name="id">
        <xsl:call-template name="valid-attri">
          <xsl:with-param name="val" select="key"/>
        </xsl:call-template>
      </xsl:attribute>

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
          <xsl:value-of select="title"/>
          <xsl:call-template name="add-punct">
            <xsl:with-param name="val" select="title"/>
          </xsl:call-template>
          <xsl:text> </xsl:text>
          <!-- Journal -->
          <xsl:if test="journal">
            <em><xsl:value-of select="journal"/></em><xsl:text>, </xsl:text>
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
            <xsl:if test="not(number) and pages">&pages;&nbsp;</xsl:if>
          </xsl:if>
          <!-- Pages -->
          <xsl:if test="pages">
            <xsl:value-of select="pages"/><xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Month -->
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text>&nbsp;</xsl:text>
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
              <xsl:text>, &editors;. </xsl:text>
            </xsl:if>
          </xsl:if>
          <!-- Title -->
          <em><xsl:value-of select="title"/></em>
          <!-- Volume -->
          <xsl:if test="volume">
            <xsl:text>, &volume;&nbsp;</xsl:text><xsl:value-of select="volume"/>
            <xsl:if test="series">
              <xsl:text> &of;&nbsp;</xsl:text>
            </xsl:if>
          </xsl:if>
          <!-- Series -->
          <xsl:if test="series">
            <em><xsl:value-of select="series"/></em>
          </xsl:if>
          <xsl:choose>
            <xsl:when test="not(volume) and not(series)">
              <xsl:call-template name="add-punct">
                <xsl:with-param name="val" select="title"/>
              </xsl:call-template>
            </xsl:when>
            <xsl:otherwise>
              <xsl:text>. </xsl:text>
            </xsl:otherwise>
          </xsl:choose>
          <xsl:text> </xsl:text>

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
            <xsl:value-of select="edition"/><xsl:text>&nbsp;&edition;. </xsl:text>
          </xsl:if>
          <!-- Month -->
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text>&nbsp;</xsl:text>
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
          <em><xsl:value-of select="title"/></em>
          <!-- Volume -->
          <xsl:if test="volume">
            <xsl:text>, &volume;&nbsp;</xsl:text><xsl:value-of select="volume"/>
          </xsl:if>
          <!-- Chapter -->
          <xsl:if test="chapter">
            <xsl:text>, &chapter;&nbsp;</xsl:text><xsl:value-of select="chapter"/>
          </xsl:if>
          <xsl:if test="pages">
            <xsl:text>, &pages;&nbsp;</xsl:text><xsl:value-of select="pages"/>
          </xsl:if>
          <xsl:text>. </xsl:text>
          <xsl:if test="editor">
            <xsl:text>&in;&nbsp;</xsl:text>
            <xsl:call-template name="format-names">
              <xsl:with-param name="names" select="editor"/>
            </xsl:call-template>
            <xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Month -->
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text>&nbsp;</xsl:text>
          </xsl:if>
          <!-- Year -->
          <xsl:value-of select="year"/><xsl:text>.</xsl:text>
        </xsl:when>

        <!--========================= Booklet ===========================-->
        <xsl:when test="$item-type = 'booklet'">
          <!-- The Author -->
          <xsl:call-template name="format-names">
            <xsl:with-param name="names" select="author"/>
          </xsl:call-template>
          <xsl:text>. </xsl:text>
          <!-- Title -->
          <em><xsl:value-of select="title"/></em>
          <!-- How published -->
          <xsl:if test="howpublished">
            <xsl:call-template name="pconv-url">
              <xsl:with-param name="str" select="howpublished"/>
            </xsl:call-template>
            <xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Address -->
          <xsl:if test="address">
            <xsl:value-of select="address"/>
            <xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Month -->
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text>&nbsp;</xsl:text>
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
          <em><xsl:value-of select="title"/></em>
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
            <xsl:value-of select="month"/><xsl:if test="year"><xsl:text>&nbsp;</xsl:text></xsl:if>
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
          <xsl:text>&techreport;</xsl:text>
          <xsl:if test="number">
            <xsl:text>&nbsp;</xsl:text><xsl:value-of select="number"/>
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
            <xsl:value-of select="month"/><xsl:text>&nbsp;</xsl:text>
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
          <em><xsl:value-of select="title"/></em>
          <xsl:text>. </xsl:text>
          <xsl:text>&phdthesis;</xsl:text>
          <xsl:if test="school">
            <xsl:text>, </xsl:text><xsl:value-of select="school"/>
          </xsl:if>
          <xsl:if test="address">
            <xsl:text>, </xsl:text><xsl:value-of select="address"/>
          </xsl:if>
          <xsl:text>, </xsl:text>
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text>&nbsp;</xsl:text>
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
          <xsl:text>&mstthesis;</xsl:text>
          <xsl:if test="school">
            <xsl:text>, </xsl:text><xsl:value-of select="school"/>
          </xsl:if>
          <xsl:if test="address">
            <xsl:text>, </xsl:text><xsl:value-of select="address"/>
          </xsl:if>
          <xsl:text>, </xsl:text>
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text>&nbsp;</xsl:text>
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
            <xsl:text>, &editors;. </xsl:text>
          </xsl:if>
          <em><xsl:value-of select="title"/></em>
          <xsl:if test="address">
            <xsl:text>, </xsl:text><xsl:value-of select="address"/>
          </xsl:if>
          <xsl:text>, </xsl:text>
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text>&nbsp;</xsl:text>
          </xsl:if>
          <xsl:value-of select="year"/><xsl:text>.</xsl:text>
          <xsl:if test="organization">
            <xsl:text> </xsl:text>
            <xsl:value-of select="organization"/>
            <xsl:if test="publisher">
              <xsl:text>,</xsl:text>
            </xsl:if>
            <xsl:if test="not(publisher)">
              <xsl:text>.</xsl:text>
            </xsl:if>
          </xsl:if>
          <xsl:if test="publisher">
            <xsl:text> </xsl:text>
            <xsl:value-of select="publisher"/>
            <xsl:text>.</xsl:text>
          </xsl:if>
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
            <xsl:text> &in;&nbsp;</xsl:text>
            <xsl:call-template name="format-names">
              <xsl:with-param name="names" select="editor"/>
            </xsl:call-template>
            <xsl:text>, &editors;</xsl:text>
          </xsl:if>
          <xsl:if test="booktitle">
            <xsl:text>, </xsl:text><em><xsl:value-of select="booktitle"/></em>
          </xsl:if>
          <xsl:if test="pages">
            <xsl:text>, &pages;&nbsp;</xsl:text><xsl:value-of select="pages"/>
          </xsl:if>
          <xsl:if test="address">
            <xsl:text>, </xsl:text><xsl:value-of select="address"/>
          </xsl:if>
          <xsl:text>, </xsl:text>
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text>&nbsp;</xsl:text>
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
            <xsl:call-template name="pconv-url">
              <xsl:with-param name="str" select="howpublished"/>
            </xsl:call-template>
            <xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Month -->
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text>&nbsp;</xsl:text>
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
          <xsl:value-of select="title"/>
          <xsl:text>. </xsl:text>
          <!-- Note -->
          <xsl:if test="note">
            <xsl:value-of select="note"/><xsl:text>, </xsl:text>
          </xsl:if>
          <!-- Month -->
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text>&nbsp;</xsl:text>
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
          <em><xsl:value-of select="title"/></em><xsl:text>. </xsl:text>
          <!-- Month -->
          <xsl:if test="month">
            <xsl:value-of select="month"/><xsl:text>&nbsp;</xsl:text>
          </xsl:if>
          <!-- Year -->
          <xsl:value-of select="year"/><xsl:text>.</xsl:text>
        </xsl:otherwise>
      </xsl:choose>
    </p>

    <!-- We also add some additional Info, modify to fit your needs! -->
    <xsl:if test="abstract">
      <blockquote>
        <!-- align = justify might stress the HTML viewer! -->
        <div align="justify"><font size="-1"><b>&abstract;</b><xsl:text>  </xsl:text><xsl:value-of select="abstract"/></font></div>
      </blockquote>
    </xsl:if>
    <xsl:if test="keywords">
      <blockquote>
        <font size="-1"><b>&keywords;</b><xsl:text>  </xsl:text><xsl:value-of select="keywords"/></font>
      </blockquote>
    </xsl:if>

    <!-- And finally some links -->
    <ul>
      <xsl:if test="local-url">
        <xsl:call-template name="make-link">
          <xsl:with-param name="val" select="local-url"/>
        </xsl:call-template>
      </xsl:if>
      <xsl:if test="pdf">
        <xsl:call-template name="make-link">
          <xsl:with-param name="val" select="pdf"/>
        </xsl:call-template>
      </xsl:if>
      <xsl:if test="ps">
        <xsl:call-template name="make-link">
          <xsl:with-param name="val" select="ps"/>
        </xsl:call-template>
      </xsl:if>
      <xsl:if test="url">
        <xsl:call-template name="make-link">
          <xsl:with-param name="val" select="url"/>
        </xsl:call-template>
      </xsl:if>
      <xsl:if test="doi">
        <li>
          <xsl:call-template name="make-doi">
            <xsl:with-param name="val" select="doi"/>
          </xsl:call-template>
        </li>
      </xsl:if>

      <xsl:if test="crossref">
        <!-- We need the bib:// to tell BibEdt it's an internal link -->
        <li><a href="bib://{crossref}"><xsl:value-of select="crossref"/></a></li>
      </xsl:if>
    </ul>

  </xsl:for-each>

</body></html>
</xsl:template>
</xsl:stylesheet>
