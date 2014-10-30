//
//  SCMultiDomainViewController.h
//  academy
//
//  Created by kimberly on 10/8/13.
//  Copyright (c) 2013 gpshopper. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SCDomain.h"
#import "SCDomainUI.h"
#import "SCTableDelegate.h"


@class SCMultiDomainViewController;

@protocol SCMultiDomainViewControllerDelegate < NSObject >

@optional

-(void)scMultiDomainViewControllerConfirmedSelection: (SCMultiDomainViewController *)vc;

@end

@interface SCMultiDomainViewController : UIViewController
< SCDomainValueTableEntryDelegate,
  SCDomainTableHeaderViewDelegate >
{
    SCTableDelegate *tableDelegate;
}

@property (readonly) IBOutlet UITableView *tableView;
@property (retain, nonatomic) id<SCMultiDomainSelection> multiDomainSelection;
@property (retain, nonatomic) NSDictionary *displayableReplacementsForDomainNames;

/**
 When enabled, notifies delegate on _every_ change,
 not just confirmSelection:
 
 @default NO
 */
@property (readwrite) BOOL confirmSelectionOnChange;
@property (assign) id<SCMultiDomainViewControllerDelegate> delegate;

-(void)reloadData;

-(id<SCTableSection>)newTableSectionForDomain: (SCDomain *)d;

-(SCDomainTableSection *)newDomainTableSectionForDomain: (SCDomain *)d;

-(id<SCTableEntry>)newTableEntryForDomainValue: (SCDomainValue *)dv
                                    domainName: (NSString *)n;

-(SCDomainValueTableEntry *)newDomainValueTableEntryForDomainValue: (SCDomainValue *)dv
                                                        domainName: (NSString *)n;

/** @name Actions */

-(IBAction)confirmSelection:(id)sender;

@end
