//
//  SCTableDelegate.h
//  EXPproject
//
//  Created by kimberly on 6/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SCTABLEDELEGATE_H
#define SCTABLEDELEGATE_H

#import <Foundation/Foundation.h>


@protocol SCTableEntry;

/**
 Implementation of UITableViewDataSource and UITableViewDelegate
 in terms of SCTableSection and SCTableEntry objects.
 */

@interface SCTableDelegate : NSObject < UITableViewDataSource, UITableViewDelegate >
{
    NSMutableDictionary *cellDescsToEntries;
}

@property (readonly) NSMutableArray *sections;
@property (nonatomic, retain) UIColor *cellBgColor;

-(id<SCTableEntry>)entryForCell: (UITableViewCell *)c;

@end


/**
 Interface for table sections.
 
 This interface should be extended as need for section-related
 functions are needed.
 */
@protocol SCTableSection <NSObject>

/**
 An array of id<SCTableEntry> objects.
 
 SCTableDelegate uses this method to implement
 
     - (NSInteger)tableView:(UITableView *)tableView
      numberOfRowsInSection:(NSInteger)section
 
 in UITableViewDataSource.
 */
-(NSArray *)entries;

/** @name Header UI */

/**
 Used to implement
 
     -(NSString *)tableView: (UITableView *)tv titleForHeaderInSection: (NSInteger)s
 
 */
-(NSString *)headerTitle;

/**
 Used to implement
 
     - (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
 */
-(UIView *)headerView;

/**
 Used to implement
 
 - (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
 */
-(void)configureHeaderView: (UIView *)v;

/**
 Used to implement
 
     - (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
 */
-(double)headerHeight;

@end


/**
 Standard implementation of SCTableSection protocol.
 */

@interface SCBaseTableSection : NSObject < SCTableSection >

/**
 Protocol function 'entries' implemented as mutable array.
 */
@property (readonly) NSMutableArray *entries;
@property (copy) NSString *headerTitle;
@property (readwrite) double headerHeight;
@property (copy) NSString *headerXibFilename;

@end


/**
 Interface for table entries.
 */
@protocol SCTableEntry <NSObject>

/**
 Used to implement
 
     - (CGFloat)tableView:(UITableView *)tableView
      heightForRowAtIndexPath:(NSIndexPath *)indexPath
 
 in UITableViewDelegate.
 */
-(double)rowHeight;

/**
 Used in cell creation.
 */
-(UITableViewCellSelectionStyle)selectionStyle;


/**
 Used in cell creation.
 */
-(UITableViewCellAccessoryType)accessoryType;

/**
 Used in cell creation.
 */
-(NSString *)reuseIdentifier;

/**
 Used to implement
 
     [- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath](http://www.google.com)
 */
-(UITableViewCell *)cell;

/**
 Used to implement
 
     ...cellForRowAtIndexPath:...
 
 in UITableViewDataSource.
 */
-(void)configureCell: (UITableViewCell *)c;

/**
 Wrapper for
 
     - (void)tableView:(UITableView *)tableView
     didSelectRowAtIndexPath:(NSIndexPath *)indexPath
 
 in UITableViewDelegate.
 */
-(void)wasSelected;

/**
 Used to populate standard UITableViewCell if 'cell' returns nil.
 */
-(NSString *)text;

/**
 Used to populate standard UITableViewCell if 'cell' returns nil.
 */
-(NSString *)detailText;

/**
 Used to populate imageView, if not nil.
 */
-(UIImage *)image;

/**
 Used to create a standard UITableViewCell instance,
 if 'cell' returns nil.
 */
-(UITableViewCellStyle)cellStyle;

/**
 Used to customize the table view cell's accessory Icon.
 */
/*
 Used to provide custom fonts for the cells 
 */
-(UIFont *) cellFont;

-(UITableViewCellEditingStyle)editingStyle;

-(void)cell: (UITableViewCell *)c
wasEditedWithStyle: (UITableViewCellEditingStyle)s;

-(void)cellBeganEditing: (UITableViewCell *)c;

-(void)cellDidEndEditing: (UITableViewCell *)c;

@end


/**
 Basic implementation of SCTableEntry with mutable properties.
 */
@interface SCBaseTableEntry : NSObject < SCTableEntry >

@property (readwrite) double rowHeight;
@property (readwrite) UITableViewCellSelectionStyle selectionStyle;
@property (readwrite) UITableViewCellStyle cellStyle;
@property (readwrite) UITableViewCellEditingStyle editingStyle;
@property (readwrite) UITableViewCellAccessoryType accessoryType;
@property (copy) NSString *text;
@property (copy) NSString *detailText;
@property (copy) NSString *imageFilename;
@property (copy) NSString *reuseIdentifier;
@property (copy) NSString *xibName;

@end


@class SCDataObjectTableEntry;

@protocol SCDataObjectTableEntryDelegate < NSObject >

-(void)scDataObjectTableEntryWasSelected: (SCDataObjectTableEntry *)e;

-(void)scDataObjectTableEntryWasSelectedForDeletion: (SCDataObjectTableEntry *)e;

@end

@interface SCDataObjectTableEntry : SCBaseTableEntry
@property (retain) id dataObject;
@property (assign) id < SCDataObjectTableEntryDelegate > delegate;
@end

@interface SCDataObjectTableViewCell : UITableViewCell
@property (retain) id dataObject;
@end

#endif