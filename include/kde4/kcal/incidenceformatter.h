/*
  This file is part of the kcal library.

  Copyright (c) 2001-2003 Cornelius Schumacher <schumacher@kde.org>
  Copyright (c) 2004 Reinhold Kainhofer <reinhold@kainhofer.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Library General Public License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to
  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA 02110-1301, USA.
*/
/**
  @file
  This file is part of the API for handling calendar data and provides
  static functions for formatting Incidences for various purposes.

  @author Cornelius Schumacher \<schumacher@kde.org\>
  @author Reinhold Kainhofer \<reinhold@kainhofer.com\>
*/
#ifndef KCAL_INCIDENCEFORMATTER_H
#define KCAL_INCIDENCEFORMATTER_H

#include "kcal_export.h"
#include <KDE/KDateTime>
#include <QtCore/QString>

namespace KCal {
class Calendar;
class Incidence;
class IncidenceBase;

class KCAL_EXPORT InvitationFormatterHelper
{
  public:
    InvitationFormatterHelper() : d( 0 ) {}
    virtual ~InvitationFormatterHelper(){}
    virtual QString generateLinkURL( const QString &id );
    virtual QString makeLink( const QString &id, const QString &text );
    virtual Calendar *calendar() const;

  private:
    //@cond PRIVATE
    Q_DISABLE_COPY( InvitationFormatterHelper )
    class Private;
    Private *const d;
    //@endcond
};

/**
  @brief
  Provides methods to format Incidences in various ways for display purposes.

  Helpers that provides several static methods to format an Incidence in
  different ways: like an HTML representation for KMail, a representation
  for tool tips, or a representation for a viewer widget.

*/
namespace IncidenceFormatter
{
  /**
    Create a QString representation of an Incidence in a nice format
    suitable for using in a tooltip.
    @param incidence is a pointer to the Incidence to be formatted.
    @param richText if yes, the QString will be created as RichText.
    @param spec is an optional time specification which, when specified,
    will shift the Incidence times to different timezones.
    @since 4.2
  */
  KCAL_EXPORT QString toolTipStr( IncidenceBase *incidence,
                                  bool richText=true,
                                  KDateTime::Spec spec=KDateTime::Spec() );

  /**
    Create a QString representation of an Incidence in a nice format
    suitable for using in a tooltip.
    @param incidence is a pointer to the Incidence to be formatted.
    @param richText if yes, the QString will be created as RichText.
    @deprecated use toolTipStr( IncidenceBase *, bool, KDateTime::Spec)
  */
  KCAL_EXPORT KDE_DEPRECATED QString toolTipString( IncidenceBase *incidence,
                                                    bool richText=true );

  /**
    Create a RichText QString representation of an Incidence in a nice format
    suitable for using in a viewer widget.
    @param incidence is a pointer to the Incidence to be formatted.
    @param spec is an optional time specification which, when specified,
    will shift the Incidence times to different timezones.
    @since 4.2
  */
  KCAL_EXPORT QString extensiveDisplayStr( IncidenceBase *incidence,
                                           KDateTime::Spec spec=KDateTime::Spec() );

  /**
    Create a RichText QString representation of an Incidence in a nice format
    suitable for using in a viewer widget.
    @param incidence is a pointer to the Incidence to be formatted.
    @deprecated use extensiveDisplayStr( IncidenceBase *, KDateTime::Spec )
  */
  KCAL_EXPORT KDE_DEPRECATED QString extensiveDisplayString( IncidenceBase *incidence );

  /**
    Create a QString representation of an Incidence in format suitable for
    including inside a mail message.
    @param incidence is a pointer to the Incidence to be formatted.
    @param spec is an optional time specification which, when specified,
    will shift the Incidence times to different timezones.
    @since 4.2
  */
  KCAL_EXPORT QString mailBodyStr( IncidenceBase *incidence,
                                   KDateTime::Spec spec=KDateTime::Spec() );

/**
    Create a QString representation of an Incidence in format suitable for
    including inside a mail message.
    @param incidence is a pointer to the Incidence to be formatted.
    @deprecated use mailBodyStr( IncidenceBase *, KDateTime::Spec )
  */
  KCAL_EXPORT KDE_DEPRECATED QString mailBodyString( IncidenceBase *incidence );

  /**
    Deliver an HTML formatted string displaying an invitation.
    Use the time zone from mCalendar.
  */
  KCAL_EXPORT QString formatICalInvitation( QString invitation, Calendar *mCalendar,
                                            InvitationFormatterHelper *helper );
  /**
    @since 4.2
  */
  KCAL_EXPORT QString formatICalInvitationNoHtml( QString invitation, Calendar *mCalendar,
                                                  InvitationFormatterHelper *helper );

  /**
    Format a TNEF attachment to an HTML mail
    @since 4.1
  */
  KCAL_EXPORT QString formatTNEFInvitation( const QByteArray &tnef, Calendar *mCalendar,
                                            InvitationFormatterHelper *helper );
  /**
    Transform a TNEF attachment to an iCal or vCard
    @since 4.1
  */
  KCAL_EXPORT QString msTNEFToVPart( const QByteArray &tnef );

  /**
    Build a pretty QString representation of an Incidence's recurrence info.
    @param incidence is a pointer to the Incidence whose recurrence info
    is to be formatted.
    @since 4.1
  */
  KCAL_EXPORT QString recurrenceString( Incidence *incidence );

  /**
    Build a QString time representation of a KDateTime object.
    @param date The date to be formatted.
    @param shortfmt If true, display info in short format.
    @param spec Time spec to use.
    @see dateToString(), dateTimeToString().
    @since 4.3
  */
  KCAL_EXPORT QString timeToString( const KDateTime &date, bool shortfmt = true,
                                    const KDateTime::Spec &spec = KDateTime::Spec() );

  /**
    Build a QString date representation of a KDateTime object.
    @param date The date to be formatted.
    @param shortfmt If true, display info in short format.
    @param spec Time spec to use.
    @see dateToString(), dateTimeToString().
    @since 4.3
  */
  KCAL_EXPORT QString dateToString( const KDateTime &date, bool shortfmt = true,
                                    const KDateTime::Spec &spec = KDateTime::Spec() );

  /**
    Build a QString date/time representation of a KDateTime object.
    @param date The date to be formatted.
    @param dateOnly If true, don't print the time fields; print the date fields only.
    @param shortfmt If true, display info in short format.
    @param spec Time spec to use.
    @see dateToString(), timeToString().
    @since 4.3
  */
  KCAL_EXPORT QString dateTimeToString( const KDateTime &date,
                                        bool dateOnly = false,
                                        bool shortfmt = true,
                                        const KDateTime::Spec &spec = KDateTime::Spec() );

  class EventViewerVisitor;
  class ScheduleMessageVisitor;
  class InvitationHeaderVisitor;
  class InvitationBodyVisitor;
  class IncidenceCompareVisitor;
  class ToolTipVisitor;
  class MailBodyVisitor;
}

}

#endif
